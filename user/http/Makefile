# enable submodules
SUBMODULES 	:= 0

ifeq (1, $(SUBMODULES))

LOCAL_BASE	:= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LOCAL_MDLS	:= $(sort $(dir $(wildcard $(LOCAL_BASE)*/)))
LOCAL_MAKEFILE	:= $(filter-out $(LOCAL_BASE), $(LOCAL_MDLS))

include ./Makefile.bas

endif
