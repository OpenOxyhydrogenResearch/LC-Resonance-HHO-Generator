ifneq ($(CC),)
c_gnu := $(CC)
else
c_gnu := gcc
endif

c_gnu_libraries :=
c_gnu_optimization_options :=
