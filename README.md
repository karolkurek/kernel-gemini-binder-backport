# kernel-gemini-binder-backport
Gemini PDA kernel for SailfishOS with binder driver backported from 4.14. The intent of this backport is to allow waydroid on the Gemini+Sailfish

Building Instructions:

Download prebuilt gcc:

git clone https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9 -b nougat-release --depth 1

then:

mkdir KERNEL_OUT
cp config KERNEL_OUT/.config
make O=../KERNEL_OUT -C kernel-gemini-binder-backport ARCH=arm64 menuconfig
make O=../KERNEL_OUT -C kernel-gemini-binder-backport ARCH=arm64  CROSS_COMPILE=../aarch64-linux-android-4.9/bin/aarch64-linux-android- -j10

Flashable boot.img can be created with:

mkbootimg --cmdline 'bootopt=64S3,32N2,64N2' --kernel KERNEL_OUT/arch/arm64/boot/Image.gz-dtb --ramdisk sailfishos_boot.img-ramdisk.gz --base 0x00000000 --pagesize 2048 --kernel_offset 0x40080000 --ramdisk_offset 0x45000000 --second_offset 0x40f00000 --tags_offset 0x44000000 --board '' -o sailfishos_boot.img

config file and ramdisk are available in the RELEASE folder. Prebuilt boot.img ready to be flashed is also provided
