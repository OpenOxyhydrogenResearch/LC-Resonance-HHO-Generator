# file      : build/import/libfrontend-elements/stub.make
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2009 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

$(call include-once,$(scf_root)/import/libfrontend-elements/configuration-rules.make,$(dcf_root))

libfrontend_elements_installed :=

$(call -include,$(dcf_root)/import/libfrontend-elements/configuration-dynamic.make)

ifdef libfrontend_elements_installed

ifeq ($(libfrontend_elements_installed),y)

$(call export,l: -lfrontend-elements -lcult,cpp_options: )

else

# Include export stub.
#
$(call include,$(scf_root)/export/libfrontend-elements/stub.make)

endif

else

.NOTPARALLEL:

endif
