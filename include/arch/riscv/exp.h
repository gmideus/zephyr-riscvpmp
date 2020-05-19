/*
 * Copyright (c) 2016 Jean-Paul Etienne <fractalclone@gmail.com>
 * Copyright (c) 2018 Foundries.io Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief RISCV public exception handling
 *
 * RISCV-specific kernel exception handling interface.
 */

#ifndef ZEPHYR_INCLUDE_ARCH_RISCV_EXP_H_
#define ZEPHYR_INCLUDE_ARCH_RISCV_EXP_H_

#ifndef _ASMLANGUAGE
#include <zephyr/types.h>
#include <toolchain.h>

#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
#include <soc_context.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The name of the structure which contains soc-specific state, if
 * any, as well as the soc_esf_t typedef below, are part of the RISC-V
 * arch API.
 *
 * The contents of the struct are provided by a SOC-specific
 * definition in soc_context.h.
 */
#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
struct soc_esf {
	SOC_ESF_MEMBERS;
};
#endif

struct __esf {
	ulong_t ra;		/* return address */
	ulong_t gp;		/* global pointer */
	ulong_t tp;		/* thread pointer */

	ulong_t t0;		/* Caller-saved temporary register */
	ulong_t t1;		/* Caller-saved temporary register */
	ulong_t t2;		/* Caller-saved temporary register */
	ulong_t t3;		/* Caller-saved temporary register */
	ulong_t t4;		/* Caller-saved temporary register */
	ulong_t t5;		/* Caller-saved temporary register */
	ulong_t t6;		/* Caller-saved temporary register */

	ulong_t a0;		/* function argument/return value */
	ulong_t a1;		/* function argument */
	ulong_t a2;		/* function argument */
	ulong_t a3;		/* function argument */
	ulong_t a4;		/* function argument */
	ulong_t a5;		/* function argument */
	ulong_t a6;		/* function argument */
	ulong_t a7;		/* function argument */

	ulong_t mepc;		/* machine exception program counter */
	ulong_t mstatus;	/* machine status register */

	#ifdef CONFIG_RISCV_USER_MODE

	/* pmp configuration registers */

	ulong_t pmpcfg0;
	ulong_t pmpcfg1;
	ulong_t pmpcfg2;
	ulong_t pmpcfg3;

	/* pmp address registers */

	ulong_t pmpaddr0;
	ulong_t pmpaddr1;
	ulong_t pmpaddr2;
	ulong_t pmpaddr3;
	ulong_t pmpaddr4;
	ulong_t pmpaddr5;
	ulong_t pmpaddr6;
	ulong_t pmpaddr7;
	ulong_t pmpaddr8;
	ulong_t pmpaddr9;
	ulong_t pmpaddr10;
	ulong_t pmpaddr11;
	ulong_t pmpaddr12;
	ulong_t pmpaddr13;
	ulong_t pmpaddr14;
	ulong_t pmpaddr15;

	#endif


#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
	struct soc_esf soc_context;
#endif
};

typedef struct __esf z_arch_esf_t;
#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
typedef struct soc_esf soc_esf_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_ARCH_RISCV_EXP_H_ */
