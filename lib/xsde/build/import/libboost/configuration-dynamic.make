libboost_installed := y
libboost_suffix := $(BOOST_LIB_SUFFIX)

ifeq ($(BOOST_LINK_SYSTEM),n)
libboost_system := n
else
libboost_system := y
endif
