#ifdef CONFIG_RISCV_USER_MODE
	.text
	.globl to_umode
	.type to_umode, @function
to_umode:
	li t1, 0x1800
	csrc mstatus, t1
	li t1, 0x80
	csrw mstatus, t1
	la t0, umode_return
	csrw mepc, t0
	mret
umode_return:
	ret

  .globl yield
  .type yield, @function
yield:
  la a7, 0x2
  ecall
  ret

	.globl abort
	.type abort, @function
abort:
	la a7, 0x1
	ecall
	ret

#endif
