MDLS_INC	:=

ifeq (1, $(SUBMODULES))

	#LOCAL_MDLS	:= $(subst $(PROJECT_BASE), ., $(LOCAL_MDLS))
	MDLS_INC	+= $(addprefix -I,$(LOCAL_MDLS))
	MDLS_INC	:= $(sort $(MDLS_INC))
	
	CFLAGS 		+= $(MDLS_INC)
	CFLAGS		:= $(sort $(CFLAGS))

	PROJECT_SRCS	+= $(LOCAL_SRCS)
	PROJECT_SRCS	:= $(sort $(PROJECT_SRCS))
	
	PROJECT_OBJS	+= $(LOCAL_OBJS)
	PROJECT_OBJS	:= $(sort $(PROJECT_OBJS))
	
	PROJECT_DEPS	+= $(LOCAL_DEPS)
	PROJECT_DEPS	:= $(sort $(PROJECT_DEPS))

	SUBMAKEFILE	= $(foreach sdir, $(LOCAL_MAKEFILE), $(addprefix $(sdir), Makefile)) 
endif

include $(SUBMAKEFILE)
