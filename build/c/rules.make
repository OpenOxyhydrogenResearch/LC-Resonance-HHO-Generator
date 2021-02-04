# file      : build/c/rules.make
# author    : OPEN OXYHYDROGEN RESEARCH <OpenOxyHydrogen@gmail.com>
# copyright : Copyright (c) 2021 OPEN OXYHYDROGEN RESEARCH FOUNDATION
# license   : GNU GPL v3 + exceptions; see accompanying LICENSE file

include $(root)/Config/config.make

# Rules.
#
%.o: %.c
	$(CC) $(CPPFLAGS) $(EXTRA_CPPFLAGS) $(CFLAGS) -c $< -o $@
