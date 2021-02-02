#!/bin/sh

kill $(ps x | grep qemu-system-riscv64 | awk 'NR==1{print $1}')
