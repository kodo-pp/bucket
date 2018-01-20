LIBNAME=librawio.a

CC=cc
CFLAGS+=-Wall -Wextra -std=c99 -pedantic

CXX=g++
CXXFLAGS+=-Wall -Wextra -std=gnu++11 -pedantic

AR=ar

RM=rm

OBJS+=rawio.o

.PHONY: all clean bee setup
# Warning: `bee' target is debug one, do not use on production!

# Production .PHONY targets
all: $(EXECNAME) setup

clean:
	$(RM) -fv $(OBJS) $(LIBNAME) ../lib/librawio.a ../include/rawio.h

setup: librawio.a
	cp -v librawio.a ../lib
	cp -v rawio.h ../include
# Debug .PHONY targets
bee: clean all

# Not .PHONY targets
$(LIBNAME): $(OBJS)
	$(AR) -cq $(LIBNAME) $(OBJS)
