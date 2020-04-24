#include <kernel.h>
#include <sys/printk.h>
#include <stdarg.h>
#include <toolchain.h>


#ifdef CONFIG_RISCV_USER_MODE

#define IO_START 0x10012000
#define IO_END 0x10036000
#define CODE_START 0x20010000
#define CODE_END 0x40000000
#define DATA_START 0x80000000
#define UPPER_BOUND 0xFFFFFFFF

#define ADDR_SHIFT 2
#define CFG_MASK 0xFF
#define PMP0SHIFT 0
#define PMP1SHIFT 8
#define PMP2SHIFT 16
#define PMP3SHIFT 24
#define R (1 << 0)
#define W (1 << 1)
#define X (1 << 2)
#define OFF (0 << 3)
#define TOR (1 << 3)
#define NA4 (2 << 3)
#define NAPOT (3 << 3)

#define csrw(csr, value) ({ __asm__ volatile ("csrw " #csr ", %0" :: "r"(value)); })

void init_pmp(int *stack_start, unsigned int stack_size){

	uint32_t pmpconfig0, pmpconfig1;
	uint32_t pmpaddress0, pmpaddress1, pmpaddress2, pmpaddress3,
		pmpaddress4, pmpaddress5, pmpaddress6, pmpaddress7;

	pmpaddress0 = IO_START >> ADDR_SHIFT;
	pmpaddress1 = CODE_START >> ADDR_SHIFT;
	pmpaddress2 = CODE_END >> ADDR_SHIFT;
	pmpaddress3 = DATA_START >> ADDR_SHIFT;
	pmpaddress4 = (((uint32_t) DATA_START+0x114) >> ADDR_SHIFT);
	pmpaddress5 = ((uint32_t) stack_start >> ADDR_SHIFT);
	pmpaddress6 = (((uint32_t) stack_start + stack_size) >> ADDR_SHIFT);
	pmpaddress7 = UPPER_BOUND >> ADDR_SHIFT;

	pmpconfig0 = (((TOR)&CFG_MASK) << PMP0SHIFT) |
								(((TOR|R|W)&CFG_MASK) << PMP1SHIFT) |
								(((TOR|R|X)&CFG_MASK) << PMP2SHIFT) |
								(((TOR)&CFG_MASK) << PMP3SHIFT);

	pmpconfig1 = (((TOR|R|W)&CFG_MASK) << PMP0SHIFT) |
							 (((TOR)&CFG_MASK) << PMP1SHIFT) |
							 (((TOR|R|W)&CFG_MASK) << PMP2SHIFT) |
							 (((TOR)&CFG_MASK) << PMP3SHIFT);


	csrw(pmpaddr0, pmpaddress0);
	csrw(pmpaddr1, pmpaddress1);
	csrw(pmpaddr2, pmpaddress2);
	csrw(pmpaddr3, pmpaddress3);
	csrw(pmpaddr4, pmpaddress4);
	csrw(pmpaddr5, pmpaddress5);
	csrw(pmpaddr6, pmpaddress6);
	csrw(pmpaddr7, pmpaddress7);


	csrw(pmpcfg0, pmpconfig0);
	csrw(pmpcfg1, pmpconfig1);



}

#endif
