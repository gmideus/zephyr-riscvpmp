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

#define STACK_SIZE 512
#define PRIORITY 0

void thread_entry(int id);

K_THREAD_DEFINE(tid1, STACK_SIZE, user_wrapper, thread_entry, 1, NULL, PRIORITY, K_USER, K_NO_WAIT);
K_THREAD_DEFINE(tid2, STACK_SIZE, user_wrapper, thread_entry, 2, NULL, PRIORITY, K_USER, K_NO_WAIT);

int *stack_ptr;
volatile int stack_ptr_changed = 0; // set to 1 when stack_ptr is set

void thread_entry(int id){
    //printk("%d\n", id);
    int dummy = 1337;
    if(id == 1){
      stack_ptr = &dummy;
      stack_ptr_changed = 1;
      while(1){ //do not need this thread any more
        yield();
        //k_yield(); //for m-mode threads
      }
    }

    while(id == 2 && stack_ptr_changed == 0){ //wait until t1 has set stack_ptr
      yield();
      //k_yield();
    }

    //only t2 will come here
    printk("Global stack ptr is: %d\n", *stack_ptr); //this should not work if there is PMP due to stack_ptr pointing
                                //to the stack of t1

    printk("Dummy is: %d\n", dummy); //should not come here if there is PMP, this is mostly for C Comp Opt
}


void test_main(void)
{

}
