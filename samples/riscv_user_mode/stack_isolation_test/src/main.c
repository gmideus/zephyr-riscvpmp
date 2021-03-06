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

void change_pointer(int id);
void access_value(int id);

K_THREAD_DEFINE(tid1, STACK_SIZE, user_wrapper, change_pointer, 1, NULL, PRIORITY, K_USER, K_NO_WAIT);
K_THREAD_DEFINE(tid2, STACK_SIZE, user_wrapper, access_value, 2, NULL, PRIORITY, K_USER, K_NO_WAIT);

// K_THREAD_DEFINE(tid1, STACK_SIZE, change_pointer, 1, NULL, NULL, PRIORITY, K_USER, K_NO_WAIT);
// K_THREAD_DEFINE(tid2, STACK_SIZE, access_value, 2, NULL, NULL, PRIORITY, K_USER, K_NO_WAIT);

int *stack_ptr;
volatile int stack_ptr_changed = 0; // set to 1 when stack_ptr is set

void change_pointer(int id){
    int dummy = 1337;

    stack_ptr = &dummy;
    stack_ptr_changed = 1;

  }



void access_value(int id){
  while(!stack_ptr_changed){ //wait until t1 has set stack_ptr
    yield();
    //k_yield();
  }

  printk("Global stack ptr is: %d\n", *stack_ptr); //this should not work if there is PMP due to stack_ptr pointing

}


void test_main(void)
{

}
