CFLAGS += -Wall -Wextra -Isrc
SRCS = $(wildcard src/*.c)
TSRCS = $(wildcard tests/*.c)
OBJ = $(SRCS:.c=.o)
TEST_OBJ = $(TSRCS:.c=.o)
TESTEXE = test
LIBNAME = data_structures
STATLIB = lib$(LIBNAME).a

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
	$(CC) $(CFLAGS) -o $(TESTEXE) $(TEST_OBJ) $(LDLIBS)

cleanobj:
	$(RM) $(OBJ)

clean:
	$(MAKE) cleanobj
	$(RM) $(STATLIB)
	$(RM) $(TEST_OBJ)
	$(RM) $(TESTEXE)
	$(RM) uninstall

test:
	$(MAKE) all
	./test
