.text
.globl test_write_to_code
.type test_write_to_code, @function
test_write_to_code:
la t1, 0x204008d0
la t2, 0x00750513
//addi t2, t2, 0
sw t2, 0(t1)
ret
