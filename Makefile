CFLAGS += -Wall -Wextra -I./include/
SRC = $(wildcard src/*.c)
TSRCS = $(wildcard tests/*.c)
OBJ = $(SRC:.c=.o,)
TEST_OBJ = $(TSRCS:.c=)
LIBNAME = data_structures
STATLIB = lib$(LIBNAME).a
DESTDIR ?= ../

.PHONY: uninstall

PREFIX ?= /$(LIBNAME)/
LDLIBS += -L. -l$(LIBNAME)

all:
	$(MAKE) static
	$(MAKE) create_test

static: $(OBJ)
	$(MAKE) static_link

static_link:
	$(AR) -cvq $(STATLIB) $(OBJ)

create_test: $(TEST_OBJ)

cleanobj:
	$(RM) $(OBJ)

clean:
	$(MAKE) cleanobj
	$(RM) $(STATLIB)
	$(RM) $(TEST_OBJ)
	$(RM) uninstall
	$(RM) log* *-tests-* testing.bc some.bc

test:
	$(MAKE) all
	./tests/myscript.sh
