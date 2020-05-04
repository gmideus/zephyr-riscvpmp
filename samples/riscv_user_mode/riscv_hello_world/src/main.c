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
//extern void to_umode();
extern void to_mmode();
extern void ecall();

//extern void set_pmp(int *stack_start, int stack_size);
extern void set_int();//(int i, int *addr);

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




// void main(void)
// {
//   int *stack_start = (int *)_kernel.current->stack_info.start;
//   int stack_size = _kernel.current->stack_info.size;
//   int value = 14;
//   printk("0x%x\n", (int)stack_start);
//   printk("0x%x\n", (int)stack_start+stack_size);
//   set_pmp(stack_start, stack_size);
//   to_umode();
//   printk("Hello\n");
//   value = 88;
//   value2 = 33;
//   printk("0x%x: %d\n", &value2, value2);
//   to_mmode();
//
// }

void main(void)
{
  int *stack_start = (int *)_kernel.current->stack_info.start;
  int stack_size = _kernel.current->stack_info.size;
  int value = 14;
  printk("0x%x\n", (int)stack_start);
  printk("0x%x\n", (int)stack_start+stack_size);
  set_pmp(stack_start, stack_size);
  to_umode();
  int inject[4];
  inject[0] = 0x00750513;
  inject[1] = 0x00008067;

  printk("Hello!\n");

  int (*fun_ptr)(int) = (void *) &inject[0];
  value = (*fun_ptr)(1);
  //value = 88;
  printk("%d \n", value);
  printk("%p\n", &inject[0]);
  printk("%d\n", inject[0]);
}
