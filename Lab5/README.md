# Computer architecture 2. Processors. Lab № 5.

## Setup
```bash
export PATH=/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin:$PATH
```
```bash
export CROSS_COMPILE="ccache arm-linux-gnueabihf-"
```
```bash
export ARCH=arm
```
```bash
export KDIR=$HOME/repos/linux-stable
```

## Compile
```bash
make clean
```
```bash
make
```
```bash
cp hello1.ko $HOME/repos/busybox/_install/
```
```bash
cp hello2.ko $HOME/repos/busybox/_install/
```
```bash
cp -r inc/ $HOME/repos/busybox/_install/
```

## Rebuild
Commands for rebuild archive
```bash
cd ~/repos/busybox/_install
```
```bash
find . | cpio -o -H newc | gzip > ../rootfs.cpio.gz
```
```bash
cd ..
```

## Start QEMU
```bash
qemu-system-arm -kernel _install/boot/zImage -initrd rootfs.cpio.gz -machine virt -nographic -m 512 --append "root=/dev/ram0 rw console=ttyAMA0,115200 mem=512M"
```

## Kernel commands
```bash
modinfo hello1.ko
```
```bash
modinfo hello2.ko
```
```bash
insmod hello1.ko
```
```bash
insmod hello2.ko
```
```bash
rmmod hello2.ko
```
```bash
rmmod hello1.ko
```

## Debug commands
```bash
cat /sys/module/hello2/parameters/val
```
```bash
cat /proc/kallsyms | grep "print_hello"
```
