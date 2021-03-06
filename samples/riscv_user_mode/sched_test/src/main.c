/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <ztest.h>
#include <stdlib.h>
#include <sys/printk.h>
#include <kernel.h>

#define NUM_THREADS 8
#define THREAD_STACK_SIZE 500
#define THREAD_PRIORITY 0 //default is 0 if !PREEMPT_ENABLED
#define THREAD_YIELDS 1000 //number of yields for EACH thread
#define PERIOD 100 //number of yields to increase for each interval

int n_fib = 40;
int tids[] = {1, 2, 3, 4, 5, 6, 7, 8};

extern void yield(); //for user threads

struct k_thread worker_threads[NUM_THREADS];

K_THREAD_STACK_ARRAY_DEFINE(worker_stacks, NUM_THREADS, THREAD_STACK_SIZE);

int global_complete_counter = 0;

int fib(void *p1, void *p2, void *p3){
  int n = *((int *)p2);
  int tid = *((int *)p1);
  int f1 = 0;
  int f2 = 1;
  int term = 1;
  int i, j;
    for(i=0; i < n; i++){
      term = f1 + f2;
      f1 = f2;
      f2 = term;
      printf("%d\n", tid);
    }
  printf("Thread %d complete\n", tid);
  global_complete_counter++;
  return term;
}


/**
* This will measure the context switching between threads.
* The main thread (thread in main function) will create a number of threads
* and yield after all the threads have been created. The threads' entry function
* will only yield, so when the main thread is rescheduled again the clock is
* measured and the context switching time can be calculated.
*/
void test_main(void)
{
  u32_t start_time, stop_time, cycles_spent, nanoseconds_spent;
  int interval = PERIOD;
  for (int i = 0; i < NUM_THREADS; i++) {

		k_thread_create(&worker_threads[i],
				worker_stacks[i], THREAD_STACK_SIZE,
				user_wrapper, fib, &tids[i], &n_fib,
				THREAD_PRIORITY,
				0, K_NO_WAIT);

    //For normal threads, jump to threads_entry_point directly
    // k_thread_create(&worker_threads[i],
		// 		worker_stacks[i], THREAD_STACK_SIZE,
		// 		fib, &n_fib, NULL, NULL,
		// 		THREAD_PRIORITY,
		// 		0, K_NO_WAIT);

	}

  start_time = k_cycle_get_32();
  k_yield();
  while(global_complete_counter < NUM_THREADS){
    k_yield();
  }
  /* We got rescheduled again and we have exited while loop */
  stop_time = k_cycle_get_32();
  zassert_true(global_complete_counter == NUM_THREADS, "Not enough threads ran");
  cycles_spent = stop_time - start_time;
  nanoseconds_spent = (u32_t)k_cyc_to_ns_floor64(cycles_spent);
  printk("Execution time: %d\n", nanoseconds_spent);


}
