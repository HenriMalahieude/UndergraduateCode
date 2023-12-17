#Variables
COMPILER = g++
FLAGS = -Wall -Werror -Wuninitialized
OBJS = IntList.o SortedSet.o

#Targets

all: main.cpp $(OBJS)
	$(COMPILER) $(FLAGS) main.cpp $(OBJS) -o main.exe

IntList.o: IntList.cpp IntList.h
	$(COMPILER) $(FLAGS) -c IntList.cpp

SortedSet.o: SortedSet.h SortedSet.cpp IntList.h
	$(COMPILER)  $(FLAGS) -c SortedSet.cpp

clean:
	rm -rf *.o main.exe