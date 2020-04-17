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

extern void test_write_to_code();

int add_one(int a){
  return a + 1;
}

void write_to_code_area(){
  test_write_to_code();
  //int (*fun_ptr)(int) = (void*) &add_one;
  int volatile * const fun_addr_ptr = (int *) &add_one;
  *fun_addr_ptr = 0x00750513;
  printk("%x\n", &fun_addr_ptr);
  printk("%x\n", fun_addr_ptr);
  //printk("%x\n", *fun_ptr);
  printk("%x\n", *fun_addr_ptr);
  int n = 1;
  n = add_one(n);
  printk("%d\n", n);

  n = 0x2;
  printk("%d\n", n);
  int * p = &n;
  *p = 0x3;
  printk("%d\n", n);
}


void test_main(void)
{
  int n = 1;
  write_to_code_area();
  n = add_one(n);
  printk("%d\n", n);
}
