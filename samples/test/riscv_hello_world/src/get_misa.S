	.text
	.globl get_mstatus
	.type get_mstatus, @function
get_misa:
	csrr a0, misa
	ret
