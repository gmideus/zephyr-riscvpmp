
#include <kernel.h>

int is_user(){
	return (_kernel.current->base.user_options & K_USER);
}
