/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

int glovar = 17;
int glovar2 = 44;

void main(void)
{
	int array[3];
	array[0] = 1;
	array[1] = 2;
	array[2] = 3;
	printk("Hello World! %d\n", array[1]);
}
