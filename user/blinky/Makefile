FLASH_SIZE	:= 4MB
# enable submodules
SUBMODULES 	= 1

#**********************************************************************
ifeq (1, $(SUBMODULES))


LOCAL_TARGET	:= tcp

LOCAL_BASE	:= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BUILD_BASE	:= $(PROJECT_BASE)/build/$(LOCAL_TARGET)
FIRM_BASE	:= $(BUILD_BASE)
#======================================================================
LOCAL_MDLS	:= $(sort $(dir $(wildcard $(LOCAL_BASE)*/)))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)*.h)


LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)*.c)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.c))

LOCAL_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))

#======================================================================
PROJECT_OBJS	+= $(LOCAL_OBJS)
CFLAGS		+= $(addprefix -I,$(LOCAL_BASE))
#======================================================================
LOCAL_LIB	:= $(addsuffix .a, $(LOCAL_TARGET))
LOCAL_LIBS_AR	:= $(addprefix $(BUILD_BASE)/, $(LOCAL_LIB))
LIBS_AR		:= $(LOCAL_LIBS_AR)

LOCAL_OUT	:= $(patsubst %.a, %.out, $(LIBS_AR))
OUTS		+= $(LOCAL_OUT)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@
	@$(CC) $< -MM -MT $@ >> $@
	
$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)

LOCAL_MAKEFILE	:= $(filter-out $(LOCAL_BASE), $(LOCAL_MDLS))
	
include $(PROJECT_BASE)/Makefile.bas

#**********************************************************************
endif
