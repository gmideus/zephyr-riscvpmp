    .text
    .globl privilege
    .type privilege, @function
privilege:
    addi s3, x0, 2
    ecall
    ret

  .globl to_umode
  .type to_umode, @function
to_umode:
  //li t1, 0x1800
  //csrc mstatus, t1
  li t1, 0x80
  csrw mstatus, t1
  la t0, umode_return
  csrw mepc, t0
	mret
umode_return:
  ret

  .globl ecall
  .type ecall, @function
ecall:
	ecall
  /* Some dummy instructions */
  addi t0, t0, 2
  addi t0, t0, 4
	ret

  .globl set_pmp
  .type set_pmp, @function
set_pmp:
  srli t0, a0, 0x2
  csrw pmpaddr1, t0
  addi t1, a0, 0x4
  srli t1, t1, 0x2
  csrw pmpaddr2, t1
  li t1, 0x080808
  csrw pmpcfg0, t1
  ret


  .globl test_pmp
  .type test_pmp, @function
test_pmp:
  li t0, 0xff
  csrc pmpcfg0, t0
  la t1, 0xffffffff
  csrw pmpaddr0, t1
  ret
