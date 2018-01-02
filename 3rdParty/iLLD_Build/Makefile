
# get CFILES and SRCDIR
include ./cfiles.mk
#get INCLUDES
include ./inc.mk

OBJDIR := ./obj

PROG := lib/libiLLD.a
CFLAGS := -DIFX_TC27x -DIFX_USE_SW_MANAGED_INT $(INCLUDES) -Os -fdata-sections -ffunction-sections -g3 -Wall -c -fmessage-length=0 -c -mcpu=tc27xx 
LDFLAGS := -r

CC := tricore-gcc
AR := tricore-ar

OBJECTS := $(CFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CFGSRC:= ./src/ifx_cfg.c
CFGOBJ:= $(OBJDIR)/ifx_cfg.o
.DEFAULT_GOAL := all

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo 'Building file: $<'
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< > /dev/null
	@$(CC) -c $(CFLAGS) $< -E -o $(@:%.o=%.i)

$(CFGOBJ): $(CFGSRC)
	@echo 'Building file: $<'
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< > /dev/null
	@$(CC) -c $(CFLAGS) $< -E -o $(@:%.o=%.i)

$(PROG) : $(OBJECTS) $(CFGOBJ)
	@echo 'Linking: $@'
	@mkdir -p $(@D)
	@$(AR) $(LDFLAGS) -o $@ $^ >/dev/null

all: $(PROG)

clean :
	rm -f $(PROG)
	rm -rf $(OBJDIR)/*

