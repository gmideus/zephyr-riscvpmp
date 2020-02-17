.text
.globl get_ustatus
.type get_ustatus, @function
get_ustatus:
csrr a0, ustatus
ret

.globl set_ustatus
.type set_ustatus, @function
set_ustatus:
csrw ustatus, a0
ret
