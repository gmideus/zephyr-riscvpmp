#include <kernel.h>

extern void to_umode();
void init_pmp(int *stack_start, int stack_size);

void user_wrapper(void (*entry)(), void *p1, void *p2){
	init_pmp((int *)_kernel.current->stack_info.start, _kernel.current->stack_info.size);
	to_umode();
	entry(p1, p2);

}
