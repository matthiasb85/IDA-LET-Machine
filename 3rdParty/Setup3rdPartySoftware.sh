#!/bin/bash
D_FOLDER=Download
ERIKA_FOLDER=RT-Druid
ERIKA_ARC=EE_RT-Druid_2.8.0.zip
ERIKA_URL=http://www.erika-enterprise.com/erika-builds/ee_280/CLI/$ERIKA_ARC
AURIX_ILLD=AURIX_iLLD_Package_TC2xx_v1.0.1.3.0
AURIX_ILLD_ARC=${AURIX_ILLD}.zip
ILLD_FOLDER=iLLD_1_0_1_3_0
ILLD_ARC=${ILLD_FOLDER}__TC27D.zip

function clean_3rdparty {
  echo "Remove old 3rd party software"
  rm -rf $ILLD_FOLDER
  rm -rf $ERIKA_FOLDER
}

function clean_download {
  echo "Remove old archives"
  cd $D_FOLDER
  rm $ERIKA_ARC
  rm $ILLD_ARC
  cd ..
}

function get_iLLD {
  echo "Can't find Infineon iLLD!"
  echo "  1.) Please get in contact with Infineon"
  echo "  2.) Download the $AURIX_ILLD driver package"
  echo "  3.) Copy $AURIX_ILLD_ARC to ./3rdParty/$D_FOLDER"
  echo "  4.) Run 'make'/'make prepare' in ./Example  or Setup3rdPartySoftware.sh in ./3rdParty"
  exit -1
}

function download_archieve {
  echo "Download archives"
  [ ! -f ./$D_FOLDER/$ERIKA_ARC ] && wget -P ./$D_FOLDER/ $ERIKA_URL
  [ ! -f ./$D_FOLDER/$ILLD_ARC ] && [ ! -f ./$D_FOLDER/$AURIX_ILLD_ARC ] && get_iLLD
}

function extract_archieve {
  echo "Extract archives"
  unzip ./$D_FOLDER/$ERIKA_ARC > /dev/null
  [ ! -f ./$D_FOLDER/$ILLD_ARC ] && unzip -j ./$D_FOLDER/$AURIX_ILLD_ARC $AURIX_ILLD/$ILLD_ARC -d ./$D_FOLDER > /dev/null
  unzip ./$D_FOLDER/$ILLD_ARC > /dev/null
}

function apply_patches {
  echo "Apply patches"
  for file in ./Patches/*
  do
    patch -p0 < $file
  done
}

function illd_build {
  cd iLLD_Build
  echo "Compile iLLD... "
  make -j 4
  echo "...done"
  cd ..
}

function illd_clean {
  cd iLLD_Build
  make clean
  cd ..
}

case "$1" in
  clean)  illd_clean
	  clean_download
	  clean_3rdparty
	  ;;
  force)  clean_download
          clean_3rdparty
          download_archieve
          extract_archieve
          apply_patches
          illd_build
          ;;
  *)      clean_3rdparty
          download_archieve
          extract_archieve
          apply_patches
          illd_build
          ;;
esac
