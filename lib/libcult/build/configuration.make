# file      : build/configuration.make
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2006-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

$(call include-once,$(scf_root)/configuration-rules.make,$(dcf_root))


# Dynamic configuration.
#
cult_dr :=
cult_threads :=
cult_network :=


$(call -include,$(dcf_root)/configuration-dynamic.make)

ifdef cult_dr

$(out_root)/%: cult_threads := $(cult_threads)
$(out_root)/%: cult_network := $(cult_network)
$(out_root)/%: cult_dr := $(cult_dr)

else

.NOTPARALLEL:

endif
