EXECNAME?=main

CC=cc
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -D_PROJECT_VERSION=$(VERSION) -Iinclude

CXX=g++
CXXFLAGS+=-Wall -Wextra -std=gnu++11 -pedantic -D_PROJECT_VERSION=$(VERSION) -Iinclude

LIBS+=-lrawio
LDFLAGS+=-Llib
LD=$(CXX)

RM=rm

OBJS+=src/main.o

.PHONY: all clean run ee bee
# Warning: `ee' and `bee' targets are debug ones, do not use on production!

# Production .PHONY targets
all: lib/librawio.a $(EXECNAME)

clean:
	$(RM) -fv $(OBJS) $(EXECNAME)
	make clean -C rawio

run: lib/librawio.a $(EXECNAME)
	./$(EXECNAME)

# Debug .PHONY targets
ee: clean run
bee: clean all

# Not .PHONY targets
$(EXECNAME): $(OBJS) lib/librawio.a
	$(LD) $(OBJS) $(LDFLAGS) $(LIBS) -o $(EXECNAME)

# Libraries
lib/librawio.a: rawio/Makefile
	make -C rawio
