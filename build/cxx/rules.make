# file      : build/cxx/rules.make
# author    : OPEN OXYHYDROGEN RESEARCH <OpenOxyHydrogen@gmail.com>
# copyright : Copyright (c) 2021 OPEN OXYHYDROGEN RESEARCH FOUNDATION
# license   : GNU GPL v3 + exceptions; see accompanying LICENSE file

include $(root)/build/config.make

# Rules.
#
%.o: %.cxx
	$(CXX) $(CPPFLAGS) $(EXTRA_CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%: %.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
ifneq ($(POSTLD),)
	$(POSTLD) $@ $^ $(LIBS)
endif
