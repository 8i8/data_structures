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
	DS_Vector.c \
	DS_Vector_test.c \
	DS_BinarySearch.c \
	DS_BinarySearch_test.c \
	DS_Qsort.c \
	DS_Qsort_test.c \
	DS_Stack_ptr.c \
	widget.c \
	WI_histogram.c \
	random_data.c \
	DS_Trie.c \
	DS_Trie_test.c \
	DS_Heap.c \
	GE_string.c
OBJ = $(SRC:.c=.o)
CC  = gcc

CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer
#LFLAGS += -lm

vpath %.c src/ src/data_structures/ src/general/ src/tests/ src/widgets
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
	DS_DLinkedList.h \
	DS_DLinkedList_test.h \
	DS_Vector.h \
	DS_Vector_test.h \
	DS_BinarySearch.h \
	DS_BinarySearch_test.h \
	DS_Qsort.h \
	DS_Qsort_test.h \
	DS_Stack_ptr.h \
	widget.h \
	WI_histogram.h \
	random_data.h \
	DS_Trie.h \
	DS_Heap.h \
	GE_string.h
