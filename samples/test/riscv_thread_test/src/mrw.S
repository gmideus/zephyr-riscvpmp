	.text
	.globl get_reg
	.type get_reg, @function
get_reg:
	csrr a0, mie
	ret

	.globl set_reg
	.type set_reg, @function
set_reg:
	csrs mie, a0
	ret

	.globl clear_reg
	.type clear_reg, @function
clear_reg:
	csrc mie, a0
	ret
