# Globally set default goal to `all`
.DEFAULT_GOAL := all

PROJECT_APP		?= $(PROJECT_BASE)/user
PROJECT_DEBUG		?= $(PROJECT_BASE)/debug
PROJECT_INCLUDE		?= $(PROJECT_BASE)/include
PROJECT_PERIPH		?= $(PROJECT_BASE)/periph
PROJECT_DRIVER		?= $(PROJECT_BASE)/driver
PROJECT_NET		?= $(PROJECT_BASE)/net
PROJECT_HTTP		?= $(PROJECT_BASE)/http
PROJECT_COMMON		?= $(PROJECT_BASE)/common

__PROJECT_DIRECTORY_VARIABLES := 	\
	PROJECT_APP			\
	PROJECT_DEBUG			\
	PROJECT_INCLUDE			\
	PROJECT_PERIPH			\
	PROJECT_DRIVER			\
	PROJECT_NET			\
	PROJECT_DRIVER			\
	PROJECT_HTTP			\
	PROJECT_COMMON	

override PROJECT_APP		:= $(abspath $(PROJECT_APP))
override PROJECT_DEBUG		:= $(abspath $(PROJECT_DEBUG))
override PROJECT_INCLUDE	:= $(abspath $(PROJECT_INCLUDE))
override PROJECT_NET		:= $(abspath $(PROJECT_NET))
override PROJECT_DRIVER		:= $(abspath $(PROJECT_DRIVER))
override PROJECT_HTTP		:= $(abspath $(PROJECT_HTTP))
override PROJECT_COMMON		:= $(abspath $(PROJECT_COMMON))

# Ensure that all directories are set and don't contain spaces.
ifneq (, $(filter-out 1, $(foreach v,$(__PROJECT_DIRECTORY_VARIABLES),$(words $($(v))))))
  $(info Aborting compilation for your safety.)
  $(info Related variables = $(__PROJECT_DIRECTORY_VARIABLES))
  $(error Make sure no path override is empty or contains spaces!)
endif

# Use absolute paths in recusive "make" even if overriden on command line.
PROJECT_MAKEOVERRIDES 	+= $(sort $(foreach v,$(__PROJECT_DIRECTORY_VARIABLES),$($(v))))

# include all make file
PROJECT_INCLUDE_MAKEFILE += $(foreach sdir, $(PROJECT_MAKEOVERRIDES), $(addprefix $(sdir)/, Makefile))

include $(PROJECT_INCLUDE_MAKEFILE)
