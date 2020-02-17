    .text
    .globl get_mstatus
    .type get_mstatus, @function
get_mstatus:
    csrr a0, mstatus
    ret

  .globl set_mstatus
  .type set_mstatus, @function
set_mstatus:
	csrs mstatus, a0
	ret

  .globl clear_mstatus
  .type clear_mstatus, @function
clear_mstatus:
  csrc mstatus, a0
  ret
