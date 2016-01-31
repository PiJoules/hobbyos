#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/hobbyos.kernel isodir/boot/hobbyos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "hobbyos" {
    multiboot /boot/hobbyos.kernel
}
EOF
grub-mkrescue -o hobbyos.iso isodir
