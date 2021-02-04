root := ..

include $(root)/config/config.make
include $(root)/config/c/rules.make
include $(root)/config/cxx/rules.make

EXTRA_CPPFLAGS := -I..

src := main.cpp

#
#
obj := $(src:.c=.o)
obj := $(obj:.cxx=.o)

# Build.
#
main.exe: $(obj)
	$(AR) $(ARFLAGS) $@ $^
ifneq ($(RANLIB),)
	$(RANLIB) $@
endif

# It is tricky to output # with both POSIX and Windows shells.
#
ifeq ($(shell echo %PATH%),%PATH%)
h := \\\#
shell_type := posix
else
h := \#
shell_type := windows
endif


# Generated.
#
.PHONY: gen
gen:


# Test.
#
.PHONY: test
test: main.exe
	@:

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f $(obj)

clean: cleanobj
