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

if [ -d $home/kernel ]; then
	dir_kn=$home/kernel
else
	dir_kn=/tmp/anykernel/kernel
fi

dtbo_aosp=$dir_kn/dtbo_aosp.img
dtbo_stock=$dir_kn/dtbo.img
if [ -f $dtbo_aosp ]; then
ui_print " "
ui_print "Choose Vendor Rom installed.."
ui_print " "
ui_print "MIUI or AOSP ?"
ui_print " "
ui_print "   Vol+ = Yes, Vol- = No"
ui_print ""
ui_print "   Yes.. MIUI"
ui_print "   No!!... AOSP"
ui_print " "
if $FUNCTION; then
	ui_print "-> MIUI selected.."
	install_os="  -> ROM : MIUI"
	cp $dtbo_stock $home/dtbo.img
else
	ui_print "-> AOSP selected.."
	install_os="  -> ROM : AOSP"
	cp $dtbo_aosp $home/dtbo.img
fi
else
	if [ -f $dtbo_stock ]; then
		cp $dtbo_stock $home/dtbo.img
	fi;
	install_os=""
fi;

dir_dtb=$dir_kn/dtb
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
				install_dt=$dtb_image_voc
			else
				ui_print "-> Include DTB with OC GPU selected.."
				install_dtb="  -> Included DTB with OC GPU..."
				install_dt=$dtb_image_oc
			fi
		else
			ui_print "-> Include DTB with OC GPU selected.."
			install_dtb="  -> Included DTB with OC GPU..."
			install_dt=$dtb_image_oc
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
				install_dt=$dtb_image_v
			else
				ui_print "-> Include DTB with Stock GPU selected.."
				install_dtb="  -> Included DTB with Stock GPU..."
				install_dt=$dtb_image
			fi
		else
			ui_print "-> Include DTB with Stock GPU selected.."
			install_dtb="  -> Included DTB with Stock GPU..."
			install_dt=$dtb_image
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
			install_dt=$dtb_image_v
		else
			ui_print "-> Include DTB with Stock GPU selected.."
			install_dtb="  -> Included DTB with Stock GPU..."
			install_dt=$dtb_image
		fi
	else
		ui_print "-> Include DTB with Stock GPU selected.."
		install_dtb="  -> Included DTB with Stock GPU..."
		install_dt=$dtb_image
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

repack_rmdk_vendor(){
	cd $vndramdisk;
	if [ -f $rdc ]; then
		rm -f $rdc
	fi
	find . | cpio -H newc -o > $vboot_dir/$rdcn;

	cd $vboot_dir;
	$bin/magiskboot compress=$vext $rdcn;
	rm -f $rdcn

	if [ -f $rdcn.$vext ]; then
		mv $vboot_dir/$rdcn.$vext $vboot_dir/$rdc
	elif [ -f $rdcn.lz4 ]; then
		mv $vboot_dir/$rdcn.lz4 $vboot_dir/$rdc
	fi
	if [ -f $rdc ]; then
		rm -f $rdc.$vext
	else
		ui_print "   Repacking ramdisk failed. Aborting...";
		batal=1
		mv $rdc.$vext $rdc
	fi
}

patch_ramdisk(){
	#modules
	if [ -d $home/kernel/ramdisk ]; then
		ui_print " - Patch ramdisk modules"
		if [ -f $rdc.gz ]; then
			mv -f $rdc.gz $rdc;
		fi
		if [ -f ramdisk.cpio ]; then
			vext=$($bin/magiskboot decompress $rdc 2>&1 | grep -v 'raw' | sed -n 's;.*\[\(.*\)\];\1;p');
		else
			ui_print "   No ramdisk found to unpack. Aborting patch ramdisk";
			batal=1
		fi;
		if [ $batal != 1 ]; then
			if [ "$vext" ]; then
				ui_print " - Decompress $rdc.$vext...";
				mv $rdc $rdc.$vext
				$bin/magiskboot decompress $rdc.$vext $rdcn;
				if [ -f $rdcn ]; then
					ui_print "   decompress $rdc.$vext success...";
				else
					batal=1
					ui_print "   decompress $rdc.$vext failed...";
				fi
			fi;
			if [ $batal != 1 ]; then
				if [ -d $vndramdisk ]; then
					rm -fr $vndramdisk
				fi
				mkdir -p $vndramdisk;
				chmod 755 $vndramdisk;
			
				if [ -d $vndramdisk ]; then
					mv $rdcn $vndramdisk/$rdc
					cd $vndramdisk
					EXTRACT_UNSAFE_SYMLINKS=1 cpio -d -F $rdc -i;
					if [ -d $vndramdisk/lib/modules ]; then
						ui_print " - Updating modules...";
						if [ -f $vndramdisk/lib/modules/sched-walt.ko ]; then
							mv $home/kernel/ramdisk/sched-walt.ko $vndramdisk/lib/modules/sched-walt.ko
							if [ ! -f $home/kernel/ramdisk/sched-walt.ko ]; then
								ui_print "   Updating success...";
							else
								ui_print "   Updating failed...";
								if [ -d $vndramdisk ]; then
									rm -fr $vndramdisk
								fi
							fi
						else
							batal=1
							ui_print "   Updating failed... skip patch modules vendor_boot";
							if [ -d $vndramdisk ]; then
								rm -fr $vndramdisk
							fi
						fi
					fi
				fi
			fi
			if [ $batal != 1 ]; then
				repack_rmdk_vendor
			fi
		fi
		if [ -d $vndramdisk ]; then
			rm -fr $vndramdisk
		fi
	fi
}

vboot_dir=$home/vendor_boot
block_vd=/dev/block/bootdevice/by-name/vendor_boot$get_slot
vndramdisk=$vboot_dir/ramdisk;
rdc=ramdisk.cpio
rdcn=ramdisk-new.cpio
vendorboot_main(){
#Vendor Boot Patch
if [ -f $install_dt ]; then
	batal=0
	if [ ! -d $vboot_dir ]; then
		mkdir -p $vboot_dir
	fi;
	ui_print " - Getting DTB image"
	dd if=$block_vd of=$vboot_dir/boot.img
	if [ -f $vboot_dir/boot.img ]; then
		cd $vboot_dir;
		ui_print " - Unpack DTB image"
		$bin/magiskboot unpack -h $vboot_dir/boot.img;
		ui_print " - Patch DTB image"
		if [ -f $vboot_dir/dtb ]; then
			rm -f $vboot_dir/dtb
		fi;
		mv $install_dt $vboot_dir/dtb
		
		#Patch ramdisk
		#patch_ramdisk

		ui_print " - Repack DTB image"
		$bin/magiskboot repack -n $vboot_dir/boot.img $vboot_dir/vendor_boot.img;
		if [ -f $vboot_dir/vendor_boot.img ]; then
			dd if=$vboot_dir/vendor_boot.img of=$block_vd
			ui_print " - Patch DTB image success"
			ui_print " "
		else
			ui_print " - Patch DTB image failed"
			ui_print " "
		fi;
		
		cd $home
		rm -fr $vboot_dir
	else
		ui_print " - Error while getting DTB image"
		ui_print "   Can't get slot on vendor boot"
		ui_print " "
	fi;
fi;
}

extract_erofs() {
	local img_file=$1
	local out_dir=$2

	${bin}/extract.erofs -i $img_file -x -T8 -o $out_dir &> /dev/null
}

mkfs_erofs() {
	local work_dir=$1
	local out_file=$2

	local partition_name=$(basename $work_dir)

	${bin}/mkfs.erofs \
		--mount-point /${partition_name} \
		--fs-config-file ${work_dir}/../config/${partition_name}_fs_config \
		--file-contexts  ${work_dir}/../config/${partition_name}_file_contexts \
		-z lz4hc \
		$out_file $work_dir
}

inject_module(){
########## CUSTOM START ##########
gagal=0
ui_print " - Start Injecting modules"
ui_print "   by Pzqqt"
ui_print " "

BOOTMODE=false;
ps | grep zygote | grep -v grep >/dev/null && BOOTMODE=true;
$BOOTMODE || ps -A 2>/dev/null | grep zygote | grep -v grep >/dev/null && BOOTMODE=true;

no_needed_kos='
atmel_mxt_ts.ko
cameralog.ko
coresight-csr.ko
coresight-cti.ko
coresight-dummy.ko
coresight-funnel.ko
coresight-hwevent.ko
coresight-remote-etm.ko
coresight-replicator.ko
coresight-stm.ko
coresight-tgu.ko
coresight-tmc.ko
coresight-tpda.ko
coresight-tpdm.ko
coresight.ko
cs35l41_dlkm.ko
f_fs_ipc_log.ko
focaltech_fts.ko
icnss2.ko
nt36xxx-i2c.ko
nt36xxx-spi.ko
qca_cld3_qca6750.ko
qcom-cpufreq-hw-debug.ko
qcom_iommu_debug.ko
qti_battery_debug.ko
rdbg.ko
spmi-glink-debug.ko
spmi-pmic-arb-debug.ko
stm_console.ko
stm_core.ko
stm_ftrace.ko
stm_p_basic.ko
stm_p_ost.ko
synaptics_dsx.ko
'

is_mounted() { mount | grep -q " $1 "; }

# Check snapshot status
# Technical details: https://blog.xzr.moe/archives/30/
${bin}/snapshotupdater_static dump &>/dev/null
rc=$?
if [ "$rc" != 0 ]; then
	ui_print " - Cannot get snapshot status via snapshotupdater_static! rc=$rc."
	if $BOOTMODE; then
		ui_print "   If you are installing the kernel in an app, try using another app."
		ui_print "   Recommend KernelFlasher:"
		ui_print "     https://github.com/capntrips/KernelFlasher/releases"
	else
		ui_print "   Please try to reboot to system once before installing!"
	fi
	ui_print "   Aborting inject vendor_dlkm..."
	gagal=1
fi
if [ $gagal != 1 ]; then
	snapshot_status=$(${bin}/snapshotupdater_static dump 2>/dev/null | grep '^Update state:' | awk '{print $3}')
	ui_print " - Current snapshot state: $snapshot_status"
	if [ "$snapshot_status" != "none" ] && [ $gagal != 1 ]; then
		ui_print " "
		ui_print "   Seems like you just installed a rom update."
		if [ "$snapshot_status" == "merging" ]; then
			ui_print "   Please use the rom for a while to wait for"
			ui_print "   the system to vextlete the snapshot merge."
			ui_print "   It's also possible to use the \"Merge Snapshots\" feature"
			ui_print "   in TWRP's Advanced menu to instantly merge snapshots."
		else
			ui_print "   Please try to reboot to system once before installing!"
		fi
		ui_print "   Aborting inject vendor_dlkm..."
		gagal=1
	fi
	unset rc snapshot_status

	if [[ $gagal != 1 ]]; then
	# Check vendor_dlkm partition status
	[ -d /vendor_dlkm ] || mkdir /vendor_dlkm
	is_mounted /vendor_dlkm || \
		mount /vendor_dlkm -o ro || mount /dev/block/mapper/vendor_dlkm${slot} /vendor_dlkm -o ro || \
			ui_print " - Failed to mount /vendor_dlkm" gagal=1

	if [ $gagal != 1 ]; then
		strings ${home}/Image 2>/dev/null | grep -E -m1 'Linux version.*#' > ${home}/vertmp

		skip_update_flag=false
		do_backup_flag=false
		if [ -f /vendor_dlkm/lib/modules/vertmp ]; then
			[ "$(cat /vendor_dlkm/lib/modules/vertmp)" == "$(cat ${home}/vertmp)" ] && skip_update_flag=true
		else
			do_backup_flag=true
		fi
		umount /vendor_dlkm

		# Fix unable to mount image as read-write in recovery
		$BOOTMODE || setenforce 0

		ui_print " "
		if $skip_update_flag; then
			ui_print " - No need to update /vendor_dlkm partition."
		else
			# Dump vendor_dlkm partition image
			dd if=/dev/block/mapper/vendor_dlkm${slot} of=${home}/vendor_dlkm.img

			# Backup kernel and vendor_dlkm image
			if $do_backup_flag; then
				ui_print " - It looks like you are installing D8G Kernel for the first time."
				ui_print "   Next will backup the kernel and vendor_dlkm partitions..."

				build_prop=/system/build.prop
				[ -d /system_root/system ] && build_prop=/system_root/$build_prop
				backup_package=/sdcard/D8G_Kernel-restore-$(date +"%Y%m%d-%H%M%S").zip
				${bin}/7za a -tzip -bd $backup_package \
					${home}/META-INF ${bin} ${home}/LICENSE ${home}/_restore_anykernel.sh ${split_img}/kernel ${home}/vendor_dlkm.img
				${bin}/7za rn -bd $backup_package kernel Image
				${bin}/7za rn -bd $backup_package _restore_anykernel.sh anykernel.sh
				sync

				ui_print " "
				ui_print "- The current kernel and vendor_dlkm have been backedup to:"
				ui_print "  $backup_package"
				ui_print "- If you encounter an unexpected situation,"
				ui_print "  or want to restore the stock kernel,"
				ui_print "  please flash it in TWRP or some supported apps."
				ui_print " "
				touch ${home}/do_backup_flag

				unset build_prop backup_package
			fi

			ui_print "- Unpacking /vendor_dlkm partition..."
			extract_vendor_dlkm_dir=${home}/_extract_vendor_dlkm
			mkdir -p $extract_vendor_dlkm_dir
			vendor_dlkm_is_ext4=false
			extract_erofs ${home}/vendor_dlkm.img $extract_vendor_dlkm_dir || vendor_dlkm_is_ext4=true
			sync

			if $vendor_dlkm_is_ext4; then
				ui_print " - /vendor_dlkm partition seems to be in ext4 file system."
				mount ${home}/vendor_dlkm.img $extract_vendor_dlkm_dir -o ro -t ext4 || \
					ui_print " - Unsupported file system!" gagal=1
				if [ $gagal != 1 ]; then
					vendor_dlkm_free_space=$(df -k | grep -E "[[:space:]]$extract_vendor_dlkm_dir\$" | awk '{print $4}')
					umount $extract_vendor_dlkm_dir

					if [ $gagal != 1 ]; then
						[ "$vendor_dlkm_free_space" -gt 10240 ] || {
						# Resize vendor_dlkm image
						ui_print " - /vendor_dlkm partition does not have enough free space!"
						ui_print " - Trying to resize..."
						super_free_space=$(${bin}/lptools_static free | grep '^Free space' | awk '{print $NF}')
						[ "$super_free_space" -gt "$((10 * 1024 * 1024))" ] || {
							ui_print "    Super device does not have enough free space!"
							ui_print "    We have tried all known methods!"
							gagal=1
						}

						if [ $gagal != 1 ]; then
							${bin}/e2fsck -f -y ${home}/vendor_dlkm.img
							vendor_dlkm_current_size_mb=$(du -bm ${home}/vendor_dlkm.img | awk '{print $1}')
							vendor_dlkm_target_size_mb=$((vendor_dlkm_current_size_mb + 10))
							${bin}/resize2fs ${home}/vendor_dlkm.img "${vendor_dlkm_target_size_mb}M" || \
								ui_print " - Failed to resize vendor_dlkm image!" gagal=1
							if [ $gagal != 1 ]; then
								ui_print " - Resized vendor_dlkm.img size: ${vendor_dlkm_target_size_mb}M."
								# e2fsck again
								${bin}/e2fsck -f -y ${home}/vendor_dlkm.img

								unset super_free_space vendor_dlkm_current_size_mb vendor_dlkm_target_size_mb
							fi
						fi
						}

						if [ $gagal != 1 ]; then
							ui_print " - Trying to mount vendor_dlkm image as read-write..."
							mount ${home}/vendor_dlkm.img $extract_vendor_dlkm_dir -o rw -t ext4 || \
								ui_print "    Failed to mount vendor_dlkm.img as read-write!" gagal=1

							if [ $gagal != 1 ]; then
								extract_vendor_dlkm_modules_dir=${extract_vendor_dlkm_dir}/lib/modules
							fi
						fi
					fi
				fi
			else
				if [ $gagal != 1 ]; then
					extract_vendor_dlkm_modules_dir=${extract_vendor_dlkm_dir}/vendor_dlkm/lib/modules
				fi
			fi

			if [ $gagal != 1 ]; then
				ui_print " - Extracting modules..."
				${bin}/7za x -tzip $home/kernel/modules.zip
				if [ ! -d ${home}/_modules ]; then
					ui_print "    Extract modules failed!"
					gagal=1
				fi
				if [ $gagal != 1 ]; then
					ui_print " - Updating /vendor_dlkm image..."
					cp -f ${home}/_modules/*.ko ${extract_vendor_dlkm_modules_dir}/
					blocklist_expr=$(echo $no_needed_kos | awk '{ printf "-vE \^\("; for (i = 1; i <= NF; i++) { if (i == NF) printf $i; else printf $i "|"; }; printf "\)" }')
					mv -f ${extract_vendor_dlkm_modules_dir}/modules.load ${extract_vendor_dlkm_modules_dir}/modules.load.old
					cat ${extract_vendor_dlkm_modules_dir}/modules.load.old | grep $blocklist_expr > ${extract_vendor_dlkm_modules_dir}/modules.load
					rm -f ${extract_vendor_dlkm_modules_dir}/modules.load.old
					for f in $no_needed_kos; do
						rm -f ${extract_vendor_dlkm_modules_dir}/$f
					done
					cp -f ${home}/vertmp ${extract_vendor_dlkm_modules_dir}/vertmp
					sync

					if $vendor_dlkm_is_ext4; then
						set_perm 0 0 0644 ${extract_vendor_dlkm_modules_dir}/vertmp
						chcon u:object_r:vendor_file:s0 ${extract_vendor_dlkm_modules_dir}/vertmp
						umount $extract_vendor_dlkm_dir
					else
						cat ${extract_vendor_dlkm_dir}/config/vendor_dlkm_fs_config | grep -q 'lib/modules/vertmp' || \
							echo 'vendor_dlkm/lib/modules/vertmp 0 0 0644' >> ${extract_vendor_dlkm_dir}/config/vendor_dlkm_fs_config
						cat ${extract_vendor_dlkm_dir}/config/vendor_dlkm_file_contexts | grep -q 'lib/modules/vertmp' || \
							echo '/vendor_dlkm/lib/modules/vertmp u:object_r:vendor_file:s0' >> ${extract_vendor_dlkm_dir}/config/vendor_dlkm_file_contexts
						ui_print " - Repacking /vendor_dlkm image..."
						rm -f ${home}/vendor_dlkm.img
						mkfs_erofs ${extract_vendor_dlkm_dir}/vendor_dlkm ${home}/vendor_dlkm.img || \
							ui_print "    Failed to repack the vendor_dlkm image!"
						if [ $gagal != 1 ]; then
							rm -rf ${extract_vendor_dlkm_dir}
						fi
					fi

					if [ $gagal != 1 ]; then
						unset vendor_dlkm_is_ext4 vendor_dlkm_free_space extract_vendor_dlkm_dir extract_vendor_dlkm_modules_dir blocklist_expr
					fi
				fi
			fi
		fi

		if [ $gagal != 1 ]; then
			unset no_needed_kos skip_update_flag do_backup_flag

			# Patch vbmeta
			for vbmeta_blk in /dev/block/bootdevice/by-name/vbmeta${slot} /dev/block/bootdevice/by-name/vbmeta_system${slot}; do
			ui_print " - Patching ${vbmeta_blk} ..."
			${bin}/vbmeta-disable-verification $vbmeta_blk || {
				ui_print "    Failed to patching ${vbmeta_blk}!"
				ui_print "    If the device won't boot after the installation,"
				ui_print "    please manually disable AVB in TWRP."
			}
			done
		fi

	fi
	fi
fi
########## CUSTOM END ##########
}

if [ -f $home/kernel/modules.zip ]; then
	ui_print " "
	ui_print "Inject modules.."
	ui_print " "
	ui_print "Add support more feature with new module ?"
	ui_print " "
	ui_print "Required : "
	ui_print " - Decrypt"
	ui_print " "
	ui_print "   Vol+ = Yes, Vol- = No"
	ui_print " "
	ui_print "   Yes.. Inject"
	ui_print "   No!!... Skip"
	ui_print " "
	if $FUNCTION; then
		ui_print " "
		ui_print "Inject modules.."
		ui_print " "
		ui_print " Warning..."
		ui_print " "
		ui_print " The worst possibility is to fail in the vendor_dlkm inject process"
		ui_print " "
		ui_print " If injection failed you can flash backup vendor_dlkm"
		ui_print " on sdcard or you can dirty-flash previous rom"
		ui_print " "
		ui_print "Continue ?"
		ui_print " "
		ui_print "   Vol+ = Yes, Vol- = No"
		ui_print " "
		if $FUNCTION; then
			ui_print "-> Inject module Selected.."
			install_md=1
		else
			ui_print "-> Skip Inject module Selected.."
			install_md=0
		fi
	else
		ui_print "-> Skip Inject module Selected.."
		install_md=0
	fi
else
	install_md=0
fi

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
	if ! grep -q 'ro.system.build.version.sdk=35' $patch_build; then
		if ! grep -q 'ro.system.build.version.sdk=34' $patch_build; then
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
		else
			install_av="  -> Android : 13.1"
		fi
	else
		install_av="  -> Android : 14"
	fi
fi

if [ ! -f $D8G_DIR/wallset ]; then echo "Installing Wallpaper R·O·G" >> $D8G_DIR/wallset;fi;
echo "Install DKM" >> $D8G_DIR/idkm;

ui_print " "
ui_print "Installing D8G Kernel with :"
ui_print "$install_pk"
ui_print "$install_os"
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

ui_print " "
ui_print " "
ui_print "Vendor Boot"
ui_print "------------------------------------"
vendorboot_main

ui_print " "
ui_print " "
ui_print "Vendor Modules"
ui_print "------------------------------------"
# Inject
if [ $install_md = 1 ]; then
	inject_module
	if [ $gagal = 1 ]; then
		ui_print "--------"
		ui_print "Inject vendor_dlkm failed"
		ui_print "Skip inject to resume install kernel"
		ui_print " "
	fi
fi

ui_print " "
ui_print "Flashing kernel.... "
ui_print " "
