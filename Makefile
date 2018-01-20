EXECNAME?=main

CC=cc
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -D_PROJECT_VERSION=$(VERSION)

CXX=g++
CXXFLAGS+=-Wall -Wextra -std=gnu++11 -pedantic -D_PROJECT_VERSION=$(VERSION)

LIBS+=-lrawio
LDFLAGS+=-Llib
LD=$(CXX)

RM=rm

OBJS+=src/main.o

.PHONY: all clean run ee bee
# Warning: `ee' and `bee' targets are debug ones, do not use on production!

# Production .PHONY targets
all: $(EXECNAME)

clean:
	$(RM) -fv $(OBJS) $(EXECNAME)

run: $(EXECNAME)
	./$(EXECNAME)

# Debug .PHONY targets
ee: clean run
bee: clean all

# Not .PHONY targets
$(EXECNAME): $(OBJS) lib/librawio.a
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) -o $(EXECNAME)

# Libraries
lib/librawio.a: rawio/Makefile
	make -C rawio
