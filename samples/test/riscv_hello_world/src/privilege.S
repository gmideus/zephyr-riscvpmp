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
  li t1, 0x1800
  csrc mstatus, t1
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
  add a1, a1, a0
  srli a0, a0, 0x2
  srli a1, a1, 0x2
  csrw pmpaddr2, a1
  csrw pmpaddr1, a0
  la t0, 0xffffffff
  srli t0, t0, 0x2
  csrw pmpaddr3, t0
  la t1, 0x20404000 //code area
  srli t1, t1, 0x2
  csrw pmpaddr0, t1

  la t1, 0x0808080d //00->disabled, 0b->TOR+RW, 08-TOR, 0d->TOR+RX
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

  .globl set_int
  .type set_int, @function
set_int:
  lui a5, 0x80000
  li a1, 44
  sw a1, 0(a5)
  //sw a0, 0(a1)
  ret

  .globl to_mmode
  .type to_mmode, @function
to_mmode:
  la a7, 0x1
  la a1, mmode_return
  ecall
mmode_return:
  ret
