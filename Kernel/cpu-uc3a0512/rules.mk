export CROSS_LD = avr32-ld
export CROSS_CC = avr32-gcc
export CROSS_CCOPTS=-c -g -Os -fno-strict-aliasing -fomit-frame-pointer -fno-builtin -Wall -I$(ROOT_DIR)/cpu-avr32 -I$(ROOT_DIR)/platform/platform-$(TARGET) -I$(ROOT_DIR)/include -I$(ROOT_DIR) -I$(FUZIX_ROOT)/Library/include/avr32/ -I$(FUZIX_ROOT)/Library/include/ -mlongcalls -mforce-l32 -mforce-no-pic
export CROSS_AS=$(CROSS_CC) $(CROSS_CCOPTS)
export CROSS_CC_SEG1=
export CROSS_CC_SEG2=
export CROSS_CC_SEG3=
# Fixme: we should split discard off
export CROSS_CC_SEGDISC=
export CROSS_CC_VIDEO=
export CROSS_CC_FONT=
export CROSS_CC_NETWORK=
export ASOPTS=
export ASMEXT = .S
export BINEXT = .o
export BITS = 32
# Custom exec format however
