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
void access_data_ptr(int id);

K_THREAD_DEFINE(tid1, STACK_SIZE, change_pointer, 1, NULL, NULL, PRIORITY, K_USER, K_NO_WAIT);
K_THREAD_DEFINE(tid2, STACK_SIZE, user_wrapper, access_data_ptr, 2, NULL, PRIORITY, K_USER, K_NO_WAIT);

// K_THREAD_DEFINE(tid2, STACK_SIZE, access_data_ptr, 2, NULL, NULL, PRIORITY, K_USER, K_NO_WAIT);

int *data_ptr;
volatile int data_ptr_changed = 0; // set to 1 when stack_ptr is set

/**
* This is where the M-mode thread enters to set the global variable to point
* to a inaccessible address for U-mode threads in the data area.
*/
void change_pointer(int id){
    int *ptr = (int *)_kernel.current; //ptr to current thread object
    //printk("%x\n", (int)ptr);

    data_ptr = ptr;
    data_ptr_changed = 1;
}

void access_data_ptr(int id){
  while(!data_ptr_changed){ //wait until t1 has set data_ptr
    yield();
    //k_yield();
  }

  printk("Data ptr is: %x\n", (int)data_ptr); //this should not work if there is PMP
}


void test_main(void)
{

}
