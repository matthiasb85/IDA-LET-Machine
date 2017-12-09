#! /bin/bash
# script to start debugger for core_0.
# other core(s) will be started by practice script

set -e

P0_Config=./LB_scripts/config_tc27x_mc.t32
P1_PORT=10000
P2_TITLE=Tricore_CORE0
P3_TMP=/tmp
P4_SYS=/opt/t32/files
P5_TCFPORT=20000
P10_SCRIPT=./LB_scripts/t32_tc27x_mc_ram.cmm
P11_ARCH=pc_linux
P12_ADDR=""

while getopts ":hf:a:i:" option; do
  case $option in
	h) echo "usage: $0 [-h] [-f] t32_folder [-a] t32_arch [-i] address ..."; exit ;;
	f) P4_SYS="${OPTARG}" ;;
	a) P11_ARCH="${OPTARG}" ;;
	i) P12_ADDR="${OPTARG}" ;;
	?) echo "error: option -${OPTARG} is not implemented"; exit ;;
  esac
done

if [ "$P12_ADDR" == "" ]; then
  P6_PBI=USB
  P7_OPT=CORE=1
  P8_OPT=
  P9_OPT=
else
  P6_PBI=NET
  P7_OPT=NODE=$P12_ADDR
  P8_OPT=PACKLEN=1024
  P9_OPT=CORE=1
fi


T32_BASE_DIR=$P4_SYS/bin/$P11_ARCH

$T32_BASE_DIR/t32mtc-qt -c $P0_Config $P1_PORT $P2_TITLE $P3_TMP $P4_SYS $P5_TCFPORT $P6_PBI $P7_OPT $P8_OPT $P9_OPT -s $P10_SCRIPT

