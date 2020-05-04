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

struct k_thread worker_threads[NUM_THREADS];

K_THREAD_STACK_ARRAY_DEFINE(worker_stacks, NUM_THREADS, THREAD_STACK_SIZE);

int global_yield_counter = 0;

void threads_entry_point(void *p1, void *p2, void *p3){
  //yield forever
  while(1){
    global_yield_counter++;
    k_yield();
    //yield() for user threads.
  }
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
    /*
		k_thread_create(&worker_threads[i],
				worker_stacks[i], THREAD_STACK_SIZE,
				user_wrapper, threads_entry_point, INT_TO_POINTER(i), NULL,
				THREAD_PRIORITY,
				0, K_NO_WAIT);
        */
    //For normal threads, jump to threads_entry_point directly
    k_thread_create(&worker_threads[i],
				worker_stacks[i], THREAD_STACK_SIZE,
				threads_entry_point, INT_TO_POINTER(i), NULL, NULL,
				THREAD_PRIORITY,
				0, K_NO_WAIT);
	}
  zassert_true(global_yield_counter == 0, "Threads ran too soon");
  while(interval <= THREAD_YIELDS){
    start_time = k_cycle_get_32();
    k_yield();
    while(global_yield_counter < NUM_THREADS * interval){
      k_yield();
    }
    /* We got rescheduled again and we have exited while loop */
    stop_time = k_cycle_get_32();
    zassert_true(global_yield_counter == NUM_THREADS * interval, "Not enough threads ran");
    cycles_spent = stop_time - start_time;
    nanoseconds_spent = (u32_t)k_cyc_to_ns_floor64(cycles_spent);
    printk("%d context switches ran in: %u nanoseconds\n", global_yield_counter, nanoseconds_spent);
    global_yield_counter = 0;
    interval += PERIOD;
  }
}
