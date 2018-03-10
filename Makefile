EXE = datastructures
SRC = \
	driver.c \
	_ds_msg.c \
	DS_Error.c \
	DS_Message.c \
	DS_Timer.c \
	DS_Output.c \
	DS_LinkedList.c \
	DS_LinkedList_test.c \
	DS_Vector.c \
	DS_Vector_test.c \
	DS_BinarySearch.c \
	DS_BinarySearch_test.c# \
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
	_ds_msg.h \
	DS_Error.h \
	DS_Message.h \
	DS_Timer.h \
	DS_Struct.h \
	DS_Output.h \
	DS_LinkedList.h	\
	DS_LinkedList_test.h \
	DS_Vector.h \
	DS_Vector_test.h \
	DS_BinarySearch.h \
	DS_BinarySearch_test.h# \
	DS_ArrayList.h#\
	DS_BinarySort.h \
	DS_Heap.h \
	DS_PriorityQueue.h \
	DS_QuickSort.h \
	DS_Trie.h
