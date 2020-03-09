ESP_BASE	?= $(abspath $(dir $(abspath $(dir $$PWD))))
ROOT_BASE	?= $(abspath $(dir $(abspath $(ESP_BASE))))
PROJECT_BASE	?= $(CURDIR)

PROJECT_SRCS	:=
PROJECT_OBJS	:=
PROJECT_DEPS	:=

LIBS_AR		:=
LIBS		:=
OUTS		:=

EDK_BASE	:= $(ROOT_BASE)/edk
EDK_OBJS	:=
EDK_DEPS	:=
EDK_MDLS	:=

include $(EDK_BASE)/Makefile.edk

.PHONY: all checkdirs flash clean

test:
	@echo	$(ESP_BASE)
	@echo	$(ROOT_BASE)
	@echo	$(subst $(PROJECT_BASE), '', $(LOCAL_MDLS))
	@echo	$(EDK_MDLS)
	
include $(PROJECT_BASE)/Makefile.cfg
include $(PROJECT_BASE)/Makefile.inc
include $(PROJECT_BASE)/Makefile.env
include $(PROJECT_BASE)/Makefile.bas

#======================================================================
# Enviroment
#======================================================================
MKDIR	:= mkdir -p
RMDIR	:= rm -rf	
RM	:= rm -f
MV	:= mf -f
#======================================================================



