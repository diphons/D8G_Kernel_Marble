### AnyKernel3 Ramdisk Mod Script
## osm0sis @ xda-developers

### AnyKernel setup
# begin properties
properties() { '
kernel.string=D8G Kernel by diphons
do.devicecheck=1
do.modules=0
do.systemless=0
do.cleanup=1
do.cleanuponabort=0
device.name1=marble
device.name2=marblein
device.name3=ingres
device.name4=ingress
device.name5=
supported.versions=
supported.patchlevels=
'; } # end properties

### AnyKernel install

## boot shell variables
block=boot
is_slot_device=1
ramdisk_compression=auto
patch_vbmeta_flag=auto

# Begin Ramdisk Changes
. tools/install.sh;
