	.text
	.globl get_misa
	.type get_misa, @function
get_misa:
	csrr a0, misa
	ret

	.globl set_misa
	.type set_misa, @function
set_misa:
	csrs misa, a0
	ret

	.globl clear_misa
	.type  clear_misa, @function
clear_misa:
	csrc misa, a0
	ret
