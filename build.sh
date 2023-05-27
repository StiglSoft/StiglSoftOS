rm bin/*
i686-elf-as src/etc/boot.s -o bin/boot.o
i686-elf-gcc -c src/kernel.c -o bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T src/etc/linker.ld -o bin/kernel.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o
cp bin/kernel.bin src/ISO/boot/
cp src/etc/grub.cfg src/ISO/boot/grub
grub-mkrescue -o bin/StiglSoftOS.iso src/ISO
qemu-system-x86_64 -cdrom bin/StiglSoftOS.iso
