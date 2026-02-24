#!/bin/bash
set -e

ELF=build/firmware.elf
BMP=/dev/ttyACM1

arm-none-eabi-gdb -q $ELF \
  -ex "target extended-remote $BMP" \
  -ex "monitor swdp_scan" \
  -ex "attach 1" \
  -ex "load" \
  -ex "detach" \
  -ex "quit"