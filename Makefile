EXE = datastructures
SRC = \
	driver.c \
	ds_msg.c \
	DS_Error.c \
	DS_Message.c \
	DS_Timer.c \
	DS_Test_output.c \
	DS_LinkedList.c \
	DS_LinkedList_test.c \
	DS_DLinkedList.c \
	DS_DLinkedList_test.c \
	DS_ListSort.c \
	DS_ListSort_test.c \
	DS_PQLinkedList.c \
	DS_PQLinkedList_test.c \
	DS_Vector.c \
	DS_Vector_test.c \
	DS_BinarySearch.c \
	DS_BinarySearch_test.c \
	widget.c# \
	DS_BinarySort.c	\
	DS_Heap.c \
	DS_PriorityQueue.c \
	DS_QuickSort.c \
	DS_Trie.c
OBJ = $(SRC:.c=.o)
CC  = gcc

CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer
#LFLAGS += -lm

vpath %.c src/ src/data_structures/ src/abstract_data_types/ src/general/ src/tests/ src/widgets
vpath %.h src/data_structures/ src/general/ src/tests/ src/widgets

.PHONY: all clean distclean

all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LFLAGS)

clean:
	rm -f $(OBJ) a.out

distclean: clean
	rm -f datastructures a.out scratch*

$(OBJ): \
	Makefile \
	ds_msg.h \
	DS_Error.h \
	DS_Message.h \
	DS_Timer.h \
	DS_Struct.h \
	DS_Test_output.h \
	DS_LinkedList.h	\
	DS_LinkedList_test.h \
	DS_ListSort.h \
	DS_DLinkedList.h \
	DS_DLinkedList_test.h \
	DS_PQLinkedList_test.h \
	DS_ListSort.h \
	DS_Vector.h \
	DS_Vector_test.h \
	DS_BinarySearch.h \
	DS_BinarySearch_test.h \
	widget.h #\
	DS_BinarySort.h \
	DS_Heap.h \
	DS_PriorityQueue.h \
	DS_QuickSort.h \
	DS_Trie.h
