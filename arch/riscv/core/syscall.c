#include <kernel.h>

#ifdef CONFIG_RISCV_USER_MODE

void syscall_yield(){
	k_yield();
}

void syscall_abort(){
	k_thread_abort(k_current_get());
}


void handle_syscall(int call_id){
	switch (call_id) {
		case 1:
			syscall_abort();
			break;
		case 2:
			syscall_yield();
			break;
	}
}

#endif
