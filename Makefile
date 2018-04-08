EXE = compression
SRC = huffman.c \
	  char_frequency.c \
	  DS_LinkedList.c \
	  DS_Error.c \
	  DS_Message.c \
	  ds_msg.c
OBJ = $(SRC:.c=.o)
CC  = gcc

CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer
#LFLAGS += -lm

vpath %.c src/data_structures/ src/huffman_compression/ src/general/
vpath %.h src/data_structures/ src/huffman_compression/ src/general/

.PHONY: all clean distclean

all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LFLAGS)

clean:
	rm -f *.o a.out

distclean: clean
	rm -f compression a.out scratch*

$(OBJ): \
	Makefile \
	char_frequency.h \
	DS_LinkedList.h \
	DS_Error.h \
	DS_Message.h \
	ds_msg.h
