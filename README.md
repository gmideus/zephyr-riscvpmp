# Zephyr RISC-V Memory Protection

This is a prototype implementing memory protection and user mode threads for Zephyr RTOS on RISC-V.

## Compatibility

This prototype is based on Zephyr 2.2.0 and is primarily intended to run in the HiFive1 Rev B board. Running it on other boards could be possible, but has not been properly tested and all protected memory regions are based on HiFive1 Rev B.
It is possible to run it on the Qemu emulator for RV32, but as of version 4.2.0 there are parts of the Physical Memory Protection features that do not work properly which could lead to unpredictable behaviour.

## Getting started

This guide will refer to matters specific to this extension and related to RISC-V memory protection. For a general guide for starting a Zephyr project, see the official [Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html).

In order to start protected user mode threads two Kconfig options have to be enabled the first one being STACK_INFO which is an option available in Zephyr by default and the second one is RISCV_USER_MODE which is a custom option added specifically for this prototype.
With these two options enabled user mode threads can be started using a function called user_wrapper with the thread entry point as the first argument. This means that any of the standard ways of starting threads in zephyr can be used, but have to be altered slightly for user mode threads.

Example:
Starting a separate thread with the function "thread_entry" with no arguments as the starting point can normally be done using the following line:
```
K_THREAD_DEFINE(tid1, STACK_SIZE, thread_entry, NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
```
To instead start this thread as a user mode thread with memory protection enabled, the user_wrapper function replaces the entry point which is instead passed as the first argument to the user_wrapper function:
```
K_THREAD_DEFINE(tid1, STACK_SIZE, user_wrapper, thread_entry, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
```
Argument two and three will be passed to the thread entry function as the first and second arguments so to start a thread with the following function call:
```
thread_entry(24, 5);
```
The thread would be defined like this:
```
K_THREAD_DEFINE(tid1, STACK_SIZE, user_wrapper, thread_entry, 24, 5, PRIORITY, 0, K_NO_WAIT);
```

There are a number of OS functions that are not available to threads in user mode because they either require access to restricted memory sections or make use of privileged instructions that can only be executed in M-mode. One of these functions k_yield has been given a user mode equivalent simply called yield that can be used by user mode threads to let the OS schedule another thread.

## Files

The following files were changed as a part of this prototype:
- arch/riscv/core/thread.c
- arch/riscv/core/reset.S
- arch/riscv/core/offsets/offsets.c
- arch/riscv/core/isr.S
- include/arch/riscv/arch.h
- include/arch/riscv/exp.h

The following NEW files were added as a part of this prototype:
- arch/riscv/core/user_wrapper.c
- arch/riscv/core/syscall.c
- arch/riscv/core/pmp.c
- arch/riscv/core/privilege.S

