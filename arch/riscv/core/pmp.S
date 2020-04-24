	.text

	.globl set_pmpcfg
	.type set_pmp, @function
set_pmpcfg:
	csrw pmpcfg0, a0
	csrw pmpcfg1, a1
	csrw pmpcfg2, a2
	csrw pmpcfg3, a3
	ret
