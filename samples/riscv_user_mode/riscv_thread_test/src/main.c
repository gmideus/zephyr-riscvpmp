/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <stdlib.h>
#include <sys/printk.h>
#include <kernel.h>

#define NUM_THREADS 2

#define STACK_SIZE 512
#define PRIORITY 0

extern void to_umode();
extern void set_pmp(int *stack_start, int stack_size);
extern int get_mstatus();
extern void set_int(int val, int* addr);
void thread_entry();
void thread_entry_m();
//void yield();
//void user_wrapper();
extern void to_mmode();
extern void yield();


K_THREAD_DEFINE(tid1, STACK_SIZE, user_wrapper, thread_entry, 1, NULL, PRIORITY, K_USER, K_NO_WAIT);
K_THREAD_DEFINE(tid2, STACK_SIZE, user_wrapper, thread_entry, 2, NULL, PRIORITY, K_USER, K_NO_WAIT);
//K_THREAD_DEFINE(tid3, STACK_SIZE, thread_entry_m, 3, NULL, NULL, PRIORITY, 0, K_NO_WAIT);


int gloval = 17;



void thread_entry(int n){

  //gloval = 66;
  for(int i = 0; i < 5; i++){
    printk("U-Thread %d: %d\n", n, gloval);
    yield();
  }

}


void thread_entry_m(int n){

  printk("Hello, I'm an M-thread\n");
  for(int i = 0; i < 4; i++){
    printk("M-Thread %d: %d\n", n, i);
    k_yield();
  }
  int mstatus = get_mstatus();
  printk("mstatus: 0x%x\n", mstatus);
}


void main(void)
{

}



int test(){
  //This is a test function to check registers
  int x = 0;
  x = x + 4;
  return x;
}
