BUILD_DIR = ./Build
THIRD_PARTY = ../3rdParty
RT_DRUID = $(THIRD_PARTY)/RT-Druid
OIL_FILE = ./conf.oil
ILLD_LIB = $(THIRD_PARTY)/iLLD_Build/lib/libiLLD.a
RT_DRUID_SH = $(RT_DRUID)/evidence/generate_code.sh
PREPARE_SH = ./Setup3rdPartySoftware.sh
LB_START = ./LB_scripts/tc27x_mc_start.sh
OIL_MD5 = $(BUILD_DIR)/conf.md5

ELF_C0 = $(BUILD_DIR)/C0/myProject_C0.elf
ELF_C1 = $(BUILD_DIR)/C0/myProject_C1.elf
ELF_C2 = $(BUILD_DIR)/C0/myProject_C2.elf

DEBUG_P = 

ifeq ($(shell test -e $(OIL_MD5) && md5sum -c --status $(OIL_MD5) && echo -n yes),yes)
OIL_UNCHANGED = TRUE
endif

ifeq ($(shell test \! -e $(ILLD_LIB)  && echo -n no),no)
PREPARE_FIRST = TRUE
endif

ifeq ($(shell test \! -e $(RT_DRUID_SH)  && echo -n no),no)
PREPARE_FIRST = TRUE
endif

ifneq ($(strip $(addr)),)
DEBUG_P += -i $(addr)
endif
ifneq ($(strip $(t32_folder)),)
DEBUG_P += -f $(t32_folder)
endif
ifneq ($(strip $(t32_arch)),)
DEBUG_P += -a $(t32_arch)
endif

.PHONY: all

all: rt-druid compile
	@echo "Done"

ifeq ($(PREPARE_FIRST),TRUE)
$(ILLD_LIB): prepare
$(RT_DRUID_SH): prepare
endif

prepare:
	@echo "Preparing 3rdParty Software ";\
	cd $(THIRD_PARTY);\
	$(PREPARE_SH);\
	cd -;\

ifeq ($(OIL_UNCHANGED),TRUE)
rt-druid: $(RT_DRUID_SH) $(ILLD_LIB)
	@echo "$(OIL_FILE) unchanged, start build process"
else
rt-druid: $(RT_DRUID_SH) $(ILLD_LIB)
	@echo "$(OIL_FILE) changed, rebuild EE environment and start build process"
	$(RT_DRUID_SH) $(RT_DRUID) $(OIL_FILE) $(BUILD_DIR)
	md5sum $(OIL_FILE) > $(OIL_MD5)
endif

$(ELF_C0): compile
$(ELF_C1): compile
$(ELF_C2): compile

compile:
	cd $(BUILD_DIR);\
	make && echo "Compiled .elf files can be found in $(BUILD_DIR)/C[0,1,2]";\
	cd -;\

debug: $(ELF_C0) $(ELF_C1) $(ELF_C2)
	$(LB_START) $(DEBUG_P)

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	@echo "Clean 3rdParty Software! Your iLLD archieve won't be deleted!";\
        cd $(THIRD_PARTY);\
        $(PREPARE_SH) clean;\
	cd -;\
