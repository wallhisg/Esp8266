# enable submodules
SUBMODULES 	= 1

ifeq (1, $(SUBMODULES))

LOCAL_BASE	:= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LOCAL_MDLS	:= $(sort $(dir $(wildcard $(LOCAL_BASE)*/)))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)*.h)
LOCAL_INCS	+= $(SDK_INCS)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)*.c)

LOCAL_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))	

LOCAL_MAKEFILE	:= $(filter-out $(LOCAL_BASE), $(LOCAL_MDLS))


$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@
	@$(CC) $< -MM -MT $@ >> $@

$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)

include $(PROJECT_BASE)/Makefile.bas

endif


