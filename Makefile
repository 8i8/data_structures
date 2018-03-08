EXE = datastructures
SRC = \
	driver.c \
	DS_Error.c \
	DS_Timer.c \
	DS_Test_output.c \
	DS_LinkedList.c \
	DS_LinkedList_test.c \
	DS_ArrayList.c \
	DS_ArrayList_test.c# \
	DS_BinarySort.c	\
	DS_Heap.c \
	DS_PriorityQueue.c \
	DS_QuickSort.c \
	DS_Trie.c
OBJ = $(SRC:.c=.o)
CC  = gcc

CFLAGS = -Wall -Wextra -pedantic
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer

vpath %.c src/data_structures/ src/general/ src/tests/
vpath %.h src/data_structures/ src/general/ src/tests/

.PHONY: all clean distclean

all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

clean:
	rm -f $(OBJ)

distclean: clean
	rm -f datastructures a.out scratch*

$(OBJ): \
	Makefile \
	DS_Error.h \
	DS_Timer.h \
	DS_Struct.h \
	DS_Test_output.h \
	DS_LinkedList.h	\
	DS_LinkedList_test.h \
	DS_ArrayList.h \
	DS_ArrayList_test.h#\
	DS_ArrayList.h#\
	DS_BinarySort.h \
	DS_Heap.h \
	DS_PriorityQueue.h \
	DS_QuickSort.h \
	DS_Trie.h
