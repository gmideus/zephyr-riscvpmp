#include <kernel.h>

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
