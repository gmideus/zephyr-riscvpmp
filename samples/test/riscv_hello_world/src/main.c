/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <stdlib.h>
#include <sys/printk.h>
#include <kernel.h>

extern int get_mstatus();
extern void set_mstatus(int x);
extern void clear_mstatus(int x);
extern void privilege(int x);
extern int get_misa();
extern void set_misa(int x);
extern void clear_misa(int x);
extern void to_umode(void*);
extern void ecall();
extern int get_reg();
extern void set_reg(int x);
extern void clear_reg(int x);
int test();
extern void set_pmp(int *stack_start, int stack_size);
extern void test_pmp();
extern void set_int(int i, int *addr);

int value2 = 17;

void print_reg(){
  int s;
  printk("Register status:\n");
  s = get_mstatus();
  printk("mstatus = 0x%x\n", s);
  // s = get_misa();
  // printk("misa = 0x%x\n", s);
  // s = get_reg();
  // printk("mtvec = 0x%x\n", s);
}



void main(void)
{
  int *stack_start = (int *)_kernel.current->stack_info.start;
  int stack_size = _kernel.current->stack_info.size;
  int value = 14;
  set_pmp(stack_start, stack_size);
  to_umode(&main);
  //test_pmp();
  //x = get_mstatus();
  //set_mstatus(0x1888);
  set_int(44, &value2);
  //get_mstatus();
  //ecall();
  printk("Hello World! %x\n", (int) value2);
}

int test(){
  //This is a test function to check registers
  int x = 0;
  x = x + 4;
  return x;
}
