ARCH		:=armv7
CHIP_NAME	:=$(PREFIX)
OS_NAME		:=$(SYSTEM)
OS_DIR		:=system/$(OS_NAME)

DEV_INC		:=device/include
DRV_INC		:=drivers/$(CHIP_NAME)/include
APP_INC		:=application/include
ARCH_INC	:=arch/$(ARCH)/$(CHIP_NAME)/include
SYS_CFG_INC	:=$(OS_DIR)/config
SYS_SRC_INC	:=$(OS_DIR)/Source/include
SYS_PORT_INC	:=$(OS_DIR)/Source/portable/GCC/ARM_CM3
SYS_MEM_INC	:=$(OS_DIR)/Source/portable/MemMang

INCS		:= -I$(DEV_INC)
INCS		+= -I$(DRV_INC)
INCS		+= -I$(APP_INC)
INCS		+= -I$(ARCH_INC)
INCS		+= -I$(SYS_CFG_INC)
INCS		+= -I$(SYS_SRC_INC)
INCS		+= -I$(SYS_PORT_INC)
INCS		+= -I$(SYS_MEM_INC)

all:
	@echo "Build Done !"

clean:
	@echo "clean done ."
