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

void test() {

  char retbig [] = {
    0xfe, 0x01, 0x01, 0x13,     //addi sp, sp, -32
    0x00, 0x81, 0x2e, 0x23,     //sw s0, 28 (sp)
    0x02, 0x01, 0x04, 0x13,     //addi s0, sp (32)
    0x3e, 0x80, 0x07, 0x93,     //li a5, 1000
    0xfe, 0xf4, 0x26, 0x23,     //sw a5, -20 (s0)
    0x00, 0x30, 0x07, 0x93,     //li a5, 3
    0xfe, 0xf4, 0x24, 0x23,     //sw a5, -24 (s0)
    0xfe, 0xc4, 0x27, 0x03,     //lw a4, -20 (s0)
    0xfe, 0x84, 0x27, 0x83,     //lw a5, -25 (s0)
    0x02, 0xf7, 0x07, 0xb3,     //mul a5, a4, a5
    0x00, 0x07, 0x85, 0x13,     //mv a0, a5
    0x01, 0xc1, 0x24, 0x03,     //lw s0, 28 (sp)
    0x02, 0x01, 0x01, 0x13,     //addi sp, sp, 32
    0x00, 0x00, 0x80, 0x67,     //ret
  };

  char retlittle [] = {
    '\x13', '\x01', '\x01', '\xfe',     //addi sp, sp, -32
    '\x23', '\x2e', '\x81', '\x00',     //sw s0, 28 (sp)
    '\x13', '\x04', '\x01', '\x02',     //addi s0, sp (32)
    '\x93', '\x07', '\x80', '\x3e',     //li a5, 1000
    '\x23', '\x26', '\xf4', '\xfe',     //sw a5, -20 (s0)
    '\x93', '\x07', '\x30', '\x00',     //li a5, 3
    '\x23', '\x24', '\xf4', '\xfe',     //sw a5, -24 (s0)
    '\x03', '\x27', '\xc4', '\xfe',     //lw a4, -20 (s0)
    '\x83', '\x27', '\x84', '\xfe',     //lw a5, -25 (s0)
    '\xb3', '\x07', '\xf7', '\x02',     //mul a5, a4, a5
    '\x13', '\x85', '\x07', '\x00',     //mv a0, a5
    '\x03', '\x24', '\xc1', '\x01',     //lw s0, 28 (sp)
    '\x13', '\x01', '\x01', '\x02',     //addi sp, sp, 32
    '\x67', '\x80', '\x00', '\x00',     //ret
  };

  int (*fun_ptr)() = &retlittle[0];
  printk("Here we go\n");
  int a = (*fun_ptr)();
  printk("%d \n", a);
}

void test_main(void)
{
  test();
}
