default linux
prompt 0

label linux
  kernel bzImage
  append ramdisk_blocksize=4096 initrd=initrd root=/dev/ram0 $KERNEL_PARAMETERS
  

