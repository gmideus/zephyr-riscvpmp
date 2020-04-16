
#include <kernel.h>

void init_pmp(struct __esf *stack_init, char *stack_start, int stack_size){
	stack_init->pmpaddr3 = (0xffffffff >> 2);
	stack_init->pmpaddr2 = (((int)stack_start + stack_size) >> 2);
	stack_init->pmpaddr1 = ((int)stack_start >> 2);
	stack_init->pmpaddr0 = (0x20404000 >> 2);
	stack_init->pmpcfg0 = 0x080b080d;
}
