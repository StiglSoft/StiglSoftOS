sudo rm disk.img -rf
rm bin/*
i686-elf-as src/etc/boot.s -o bin/boot.o
i686-elf-gcc -w -Werror -c src/kernel.c -o bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
if [ $? -ne 0 ]; then 
    exit 1
fi
i686-elf-gcc -T src/etc/linker.ld -o bin/kernel.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o

#Create and set the disk up
dd if=/dev/zero of=disk.img bs=1M count=50
sudo losetup /dev/loop0 disk.img

#Mount the disk after formating the partition
sudo parted /dev/loop0 --script mklabel msdos mkpart primary ext4 1MiB 50% set 1
sudo parted /dev/loop0 print
sudo mkfs.ext2 /dev/loop0p1 #Deny to automount
sudo mount /dev/loop0p1 ./mnt/

#Installing the grub
sudo grub-install --target=i386-pc --boot-directory=./mnt/boot /dev/loop0

#Copy the necesary files
sudo cp ./bin/kernel.bin ./mnt/boot
sudo cp ./src/etc/grub.cfg ./mnt/boot/grub

#Finish up
sudo umount /dev/loop0p1
sudo losetup -D
sudo losetup -l

qemu-system-x86_64 -drive file=disk.img,format=raw