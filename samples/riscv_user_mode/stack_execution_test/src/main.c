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

void test();


K_THREAD_DEFINE(tid1, STACK_SIZE, user_wrapper, test, NULL, NULL, PRIORITY, K_USER, K_NO_WAIT);

/**
* CARE C OPTIMIZING
*/
void test() {

  int inject [4] = {
    0x00750513, 0x00008067, 0, 0
  };

  printk("Here we set fun ptr\n");
  int (*fun_ptr)(int) = (void *) &inject[0];
  printk("Here we go\n");
  //test_add();
  printk("%pn\n", &inject[0]);
  printk("%d\n", inject[0]);
  int a = (*fun_ptr)(1);
  printk("%d \n", a);
}

void test_main(void)
{

}
