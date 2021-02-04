# file      : cult/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

$(call include,$(bld_root)/system.make)
$(call include,$(scf_root)/configuration.make)

cxx_tun   := eh/exception.cxx

cxx_tun   += mm/new.cxx        \
             mm/counter.cxx    \
             mm/buffer.cxx

cxx_tun   += rtti/type-info.cxx

cxx_tun   += trace/log.cxx

cxx_tun   += cli/arguments.cxx       \
	     cli/file-arguments.cxx  \
             cli/scanner.cxx         \
             cli/options.cxx         \
             cli/options-parser.cxx  \
             cli/options-spec.cxx

ifeq ($(cult_threads),y)
cxx_tun   += sched/condition.cxx \
             sched/mutex.cxx     \
             sched/spin.cxx      \
             sched/thread.cxx
endif


ifeq ($(cult_network),y)
cxx_tun   += os/net/address.cxx                \
             os/net/socket.cxx                 \
             os/net/datagram-socket.cxx        \
             os/net/multicast-socket.cxx       \
             os/net/ipv4/address.cxx           \
             os/net/ipv4/datagram-socket.cxx   \
             os/net/ipv4/multicast-socket.cxx
endif


ifeq ($(cult_dr),y)
cxx_tun   += dr/xdr/input-stream.cxx  \
             dr/xdr/output-stream.cxx
endif


cxx_o   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_d   := $(cxx_o:.o=.o.d)

cult.l             := $(out_base)/cult.l
cult.l.cpp-options := $(out_base)/cult.l.cpp-options

clean     := $(out_base)/.clean


# Architectures.
#
#
#@@ arch can collide if src_root == out_root
#

# List of known architectures.
#
architectures := i386                        \
                 i386/i486                   \
                 i386/i486/i586              \
                 i386/i486/i586/i686         \
                 i386/i486/i586/i686/x86_64

# Directories with architecture-specific code.
#
arch_dirs := mm
arch := $(filter %$(host_cpu),$(architectures))

r :=
r := generic $(foreach a,$(subst /, ,$(arch)),$(eval r := $(if $r,$r/)$a)$r)

sub_archs :=
$(foreach a,$r,$(eval sub_archs := $a $(sub_archs)))

#$(warning $(sub_archs))

# $1 - sub-architecture dir (e.g. i386/i486)
#
define arch-rule

arch_targets += $(foreach d,$(arch_dirs),$(out_base)/arch/$1/cult/$d/arch)

$(out_base)/arch/$1/cult/%/arch: $(src_base)/%/arch/$1 | $(out_base)/arch/$1/cult/%/.
	$(call message,using $1,ln -s $$$$< $$$$@)
endef

arch_targets :=
$(foreach a,$(sub_archs),$(eval $(call arch-rule,$a)))


# Build.
#
$(cult.l): $(cxx_o)

ifeq ($(cult_threads),y)
$(cult.l): -lpthread
endif

$(cxx_o) $(cxx_d): $(cult.l.cpp-options)

$(cult.l.cpp-options): prefix := cult/ $(out_root)/
$(cult.l.cpp-options): value := $(addprefix -I$(out_base)/arch/,$(sub_archs))\
                                -I$(out_root)\
                                -I$(src_root)

$(cult.l.cpp-options): | $(arch_targets)

$(call include-dep,$(cxx_d))


# config.hxx
#
ifdef cult_dr
$(out_base)/config.hxx: cult_threads := $(cult_threads)
$(out_base)/config.hxx:
	@echo '// file      : cult/config.hxx'                            >$@
	@echo '// author    : automatically generated'                   >>$@
	@echo '// copyright : Copyright (c) 2006-2010 Boris Kolpackov'   >>$@
	@echo '// license   : GNU GPL v2; see accompanying LICENSE file' >>$@
	@echo '#ifndef CULT_CONFIG_HXX'                                  >>$@
	@echo '#define CULT_CONFIG_HXX'                                  >>$@
ifeq ($(cult_threads),y)
	@echo '#define CULT_THREADS'                                     >>$@
endif
	@echo '#endif // CULT_CONFIG_HXX'                                >>$@
endif

# Convenience alias for default target.
#
$(out_base)/: $(cult.l)


# Clean.
#
$(clean): $(cult.l).o.clean            \
  $(cult.l.cpp-options).clean          \
  $(out_base)/cli/mapper.hxx.m4.clean  \
  $(addsuffix .cxx.clean,$(cxx_o))     \
  $(addsuffix .cxx.clean,$(cxx_d))
	$(call message,rm $$1,rm -f -r $$1,$(out_base)/arch)
	$(call message,rm $$1,rm -f $$1,$(out_base)/config.hxx)

# How to.
#
$(call include,$(bld_root)/cxx/o-l.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(bld_root)/m4/m4.make)
