	.text

	.globl set_pmp
	.type set_pmp, @function
set_pmp:
	add a1, a1, a0
	srli a0, a0, 0x2
	srli a1, a1, 0x2
	csrw pmpaddr2, a1
	csrw pmpaddr1, a0
	la t0, 0x80005fff
	srli t0, t0, 0x2
	csrw pmpaddr3, t0
	la t1, 0x20404000 //code area
	srli t1, t1, 0x2
	csrw pmpaddr0, t1

	li t1, 0x080b080d //00->disabled, 0b->TOR+RW, 08-TOR, 0d->TOR+RX
	csrw pmpcfg0, t1
	ret
