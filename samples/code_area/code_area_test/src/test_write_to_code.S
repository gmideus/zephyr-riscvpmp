.text
.globl test_write_to_code
.type test_write_to_code, @function
test_write_to_code:
la t2, 0x00750513
sw t2, 0(a0)
ret

.globl test_func
.type test_func, @function
test_func:
addi a0, a0, 1
ret
