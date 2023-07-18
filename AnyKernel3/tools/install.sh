#!/sbin/sh

# Import Fstab
#. /tmp/anykernel/tools/fstab.sh;

patch_cmdline "skip_override" "";

install_tm=""
install_ac=""
patch_build=0
install_init=0

#get slot
get_slot=$(getprop ro.boot.slot_suffix 2>/dev/null);

#Check D8G DIR
D8G_DIR=/data/media/0/d8g
if [ ! -d $D8G_DIR ]; then
	mkdir -p $D8G_DIR;
	chmod 755 $D8G_DIR;
fi
if [ ! -d $D8G_DIR/pubg ]; then
	mkdir -p $D8G_DIR/pubg;
	chmod 755 $D8G_DIR/pubg;
fi
cekdevice=$(getprop ro.product.device 2>/dev/null);
cekproduct=$(getprop ro.build.product 2>/dev/null);
cekvendordevice=$(getprop ro.product.vendor.device 2>/dev/null);
cekvendorproduct=$(getprop ro.vendor.product.device 2>/dev/null);
for cekdevicename in $cekdevice $cekproduct $cekvendordevice $cekvendorproduct; do
	cekdevices=$cekdevicename
	break 1;
done;

# Clear
ui_print "";
ui_print "";

keytest() {
  ui_print "   Press a Vol Key..."
  (/system/bin/getevent -lc 1 2>&1 | /system/bin/grep VOLUME | /system/bin/grep " DOWN" > /tmp/anykernel/events) || return 1
  return 0
}

chooseport() {
  #note from chainfire @xda-developers: getevent behaves weird when piped, and busybox grep likes that even less than toolbox/toybox grep
  while (true); do
    /system/bin/getevent -lc 1 2>&1 | /system/bin/grep VOLUME | /system/bin/grep " DOWN" > /tmp/anykernel/events
    if (`cat /tmp/anykernel/events 2>/dev/null | /system/bin/grep VOLUME >/dev/null`); then
      break
    fi
  done
  if (`cat /tmp/anykernel/events 2>/dev/null | /system/bin/grep VOLUMEUP >/dev/null`); then
    return 0
  else
    return 1
  fi
}

chooseportold() {
  # Calling it first time detects previous input. Calling it second time will do what we want
  $bin/keycheck
  $bin/keycheck
  SEL=$?
  if [ "$1" == "UP" ]; then
    UP=$SEL
  elif [ "$1" == "DOWN" ]; then
    DOWN=$SEL
  elif [ $SEL -eq $UP ]; then
    return 0
  elif [ $SEL -eq $DOWN ]; then
    return 1
  else
    abort "   Vol key not detected!"
  fi
}

if keytest; then
  FUNCTION=chooseport
else
  FUNCTION=chooseportold
  ui_print "   Press Vol Up Again..."
  $FUNCTION "UP"
  ui_print "   Press Vol Down..."
  $FUNCTION "DOWN"
fi

# Install Kernel

# Clear
ui_print " ";
ui_print " ";

if [ -f $home/kernel/dtb/dtb ]; then
	dir_dtb=$home/kernel/dtb
else
	dir_dtb=/tmp/anykernel/kernel/dtb
fi
dtb_image=$dir_dtb/dtb
dtb_image_oc=$dir_dtb/dtb_oc
dtb_image_v=$dir_dtb/dtb_v
dtb_image_voc=$dir_dtb/dtb_ocv

if [ -f $dtb_image_oc ]; then
	ui_print " "
	ui_print "Choose GPU to install.."
	ui_print " "
	ui_print "Over Clock GPU ?"
	ui_print " "
	ui_print "   Vol+ = Yes, Vol- = No"
	ui_print ""
	ui_print "   Yes.. Over Clock GPU"
	if [ -f $dtb_image_v ]; then
		ui_print "   No!!... Stock or Under Clock GPU"
	else
		ui_print "   No!!... Stock GPU"
	fi
	ui_print " "
	if $FUNCTION; then
		if [ -f $dtb_image_voc ]; then
			ui_print " "
			ui_print "Choose GPU to install.."
			ui_print " "
			ui_print "Undervolt GPU ?"
			ui_print " "
			ui_print "   Vol+ = Yes, Vol- = No"
			ui_print ""
			ui_print "   Yes.. Undervolt GPU"
			ui_print "   No!!... Stock volt GPU"
			ui_print " "
			if $FUNCTION; then
				ui_print "-> Include DTB with UV OC GPU selected.."
				install_dtb="  -> Included DTB with UV OC GPU..."
				cp $dtb_image_voc $home/dtb
			else
				ui_print "-> Include DTB with OC GPU selected.."
				install_dtb="  -> Included DTB with OC GPU..."
				cp $dtb_image_oc $home/dtb
			fi
		else
			ui_print "-> Include DTB with OC GPU selected.."
			install_dtb="  -> Included DTB with OC GPU..."
			cp $dtb_image_oc $home/dtb
		fi
	else
		if [ -f $dtb_image_v ]; then
			ui_print " "
			ui_print "Choose GPU to install.."
			ui_print " "
			ui_print "Undervolt GPU ?"
			ui_print " "
			ui_print "   Vol+ = Yes, Vol- = No"
			ui_print ""
			ui_print "   Yes.. Undervolt GPU"
			ui_print "   No!!... Stock volt GPU"
			ui_print " "
			if $FUNCTION; then
				ui_print "-> Include DTB with UV Stock GPU selected.."
				install_dtb="  -> Included DTB with UV Stock GPU..."
				cp $dtb_image_v $home/dtb
			else
				ui_print "-> Include DTB with Stock GPU selected.."
				install_dtb="  -> Included DTB with Stock GPU..."
				cp $dtb_image $home/dtb
			fi
		else
			ui_print "-> Include DTB with Stock GPU selected.."
			install_dtb="  -> Included DTB with Stock GPU..."
			cp $dtb_image $home/dtb
		fi
	fi
else
	if [ -f $dtb_image_v ]; then
		ui_print " "
		ui_print "Choose GPU to install.."
		ui_print " "
		ui_print "Undervolt GPU ?"
		ui_print " "
		ui_print "   Vol+ = Yes, Vol- = No"
		ui_print ""
		ui_print "   Yes.. Undervolt GPU"
		ui_print "   No!!... Stock volt GPU"
		ui_print " "
		if $FUNCTION; then
			ui_print "-> Include DTB with UV Stock GPU selected.."
			install_dtb="  -> Included DTB with UV Stock GPU..."
			cp $dtb_image_v $home/dtb
		else
			ui_print "-> Include DTB with Stock GPU selected.."
			install_dtb="  -> Included DTB with Stock GPU..."
			cp $dtb_image $home/dtb
		fi
	else
		ui_print "-> Include DTB with Stock GPU selected.."
		install_dtb="  -> Included DTB with Stock GPU..."
		cp $dtb_image $home/dtb
	fi
fi

# Choose Permissive or Enforcing
ui_print " "
ui_print "Choose Default Selinux to Install.."
ui_print " "
ui_print "Permissive Or Enforcing Kernel?"
ui_print " "
ui_print "   Vol+ = Yes, Vol- = No"
ui_print ""
ui_print "   Yes.. Permissive"
ui_print "   No!!... Enforcing"
ui_print " "

if $FUNCTION; then
	ui_print "-> Permissive Kernel Selected.."
	install_pk="  -> Permissive Kernel..."
	patch_cmdline androidboot.selinux androidboot.selinux=permissive
else
	ui_print "-> Enforcing Kernel Selected.."
	install_pk="  -> Enforcing Kernel..."
	patch_cmdline androidboot.selinux androidboot.selinux=enforcing
fi

vboot_dir=$home/vendor_boot
block_vd=/dev/block/bootdevice/by-name/vendor_boot$get_slot
#Vendor Boot Patch
if [ -f $home/dtb ]; then
	ui_print " "
	ui_print " "
	ui_print "Installing D8G dtb :"
	if [ ! -d $vboot_dir ]; then
		mkdir -p $vboot_dir
	fi;
	ui_print "  -> Getting DTB image"
	dd if=$block_vd of=$vboot_dir/boot.img
	if [ -f $vboot_dir/boot.img ]; then
		cd $vboot_dir
		ui_print "  -> Unpack DTB image"
		$bin/magiskboot unpack -h boot.img;
		ui_print "  -> Patch DTB image"
		if [ -f $vboot_dir/dtb ]; then
			rm -f $vboot_dir/dtb
		fi;
		mv $home/dtb $vboot_dir/dtb
		ui_print "  -> Repack DTB image"
		$bin/magiskboot repack -n boot.img vendor_boot.img;
		if [ -f $vboot_dir/vendor_boot.img ]; then
			dd if=$vboot_dir/vendor_boot.img of=$block_vd
			ui_print "  -> Patch DTB image success"
			ui_print " "
		else
			ui_print "  -> Patch DTB image failed"
			ui_print " "
		fi;
		cd $home
		rm -fr $vboot_dir
	else
		ui_print "  -> Error while getting DTB image"
		ui_print "      Can't get slot on vendor boot"
		ui_print " "
	fi;
fi;

umount /data || true
umount /system || true
umount /vendor || true
mount -o rw /dev/block/bootdevice/by-name/data /data
mount -o rw /dev/block/bootdevice/by-name/system /system
mount -o rw /dev/block/bootdevice/by-name/vendor /vendor
if [ -f /system/build.prop ]; then
	patch_build=/system/build.prop
else
	if [ -f /system/system/build.prop ]; then
		patch_build=/system/system/build.prop
	else
		if [ -f /system_root/system/build.prop ]; then
			patch_build=/system_root/system/build.prop
		else
			if [ -f /system/system_root/system/build.prop ]; then
				patch_build=/system_root/system/build.prop
			else
				patch_build=0
			fi
		fi
	fi
fi;

if [ $patch_build = 0 ]; then
	install_av="  -> Android : Not Detected"
else
	if ! grep -q 'ro.system.build.version.sdk=33' $patch_build; then
		if ! grep -q 'ro.system.build.version.sdk=32' $patch_build; then
			if ! grep -q 'ro.system.build.version.sdk=31' $patch_build; then
				install_av="  -> Android : 11"
			else
				install_av="  -> Android : 12"
			fi
		else
			install_av="  -> Android : 12.1"
		fi
	else
			install_av="  -> Android : 13"
	fi
fi

if [ ! -f $D8G_DIR/wallset ]; then echo "Installing Wallpaper R·O·G" >> $D8G_DIR/wallset;fi;
echo "Install DKM" >> $D8G_DIR/idkm;

ui_print " "
ui_print "Installing D8G Kernel with :"
ui_print "$install_pk"
ui_print "$install_av"
ui_print "$install_dtb"

ui_print " "
ui_print "Get all D8G feature ?"
ui_print "------------------------------------"
ui_print "Download module and install it using KSU"
ui_print " "
ui_print "Note :"
ui_print "--------"
ui_print "KSU not support thermal module now,"
ui_print " "
echo 0 > $D8G_DIR/pure;

umount /system || true
umount /vendor || true
