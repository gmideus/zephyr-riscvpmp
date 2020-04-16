
Run on Arty board:
   west build -b litex_vexriscv && flterm --port=/dev/ttyUSB1 --kernel=build/zephyr/zephyr.bin
   
Run in QEMU:
   west build -b qemu_riscv32 -t run
