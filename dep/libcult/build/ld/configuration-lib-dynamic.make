ld_lib_type   := archive

ifneq ($(AR),)
ld_lib_ar     := $(AR)
else
ld_lib_ar     := ar
endif

ifneq ($(RANLIB),)
ld_lib_ranlib := $(RANLIB)
else
ld_lib_ranlib := ranlib
endif
