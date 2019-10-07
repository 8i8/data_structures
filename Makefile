SRCS = $(wildcard src/*/*.c)
SRCS += $(wildcard tests/*.c)
HDRS = $(wildcard include/*.h)
HDRS += $(wildcard tests/*.h)
OBJ = $(SRCS:.c=.o)
CC = clang

CFLAGS += -Wall -Wextra -pedantic
#CFLAGS += -Werror
CFLAGS += -g
CFLAGS += -fsanitize=address
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -fsanitize=undefined
CFLAGS += -fsanitize=float-divide-by-zero
CFLAGS += -fno-sanitize-recover=all
CFLAGS += -I./include

#LFLAGS += -lm

.PHONY: clean distclean

#ifndef VERBOSE
#.SILENT:
#endif

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	$(RM) $(OBJ) test

tags: $(SRCS) $(HDRS)
	cscope -b $^

distclean: clean
	rm -f compress a.out scratch*

$(OBJ): Makefile
