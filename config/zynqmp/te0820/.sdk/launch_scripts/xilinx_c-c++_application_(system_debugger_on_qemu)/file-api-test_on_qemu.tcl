connect -url tcp:localhost:1138
targets 8
dow /home/mbenson/git/airliner/config/zynqmp/te0820/file-api-test/Debug/file-api-test.elf
mask_write 0xff5e023c [expr (1 << 0) | 0x14] 0
mwr 0xff9a0000 0x80000218
bpadd -addr &main
