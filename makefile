dirs := src

.PHONY: all $(dirs)
all: $(dirs)

tests: test
examples: examples

$(dirs):
	$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
% :: $(dirs) ;
