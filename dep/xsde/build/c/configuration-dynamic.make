c_id       := gnu
c_optimize := n
c_debug    := n
c_rpath    := n
c_pp_extra_options := $(CPPFLAGS)
c_extra_options    := $(CFLAGS)
c_ld_extra_options := $(LDFLAGS)
c_extra_libs       := $(LIBS)

r := $(shell echo $(LDFLAGS) | sed -e 's/-L *\([^ ]*\)/-L\1/g')
r := $(patsubst -L%,%,$(filter -L%,$(r)))
r := $(shell echo $(r) | sed -e 's/ /:/g')

c_extra_lib_paths  := $(r)
