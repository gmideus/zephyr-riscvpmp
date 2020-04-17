#include <kernel.h>

#ifdef CONFIG_RISCV_USER_MODE

void syscall_yield(){
	k_yield();
}


void handle_syscall(int call_id){
	switch (call_id) {
		case 2:
			syscall_yield();
			break;
	}
}

#endif
