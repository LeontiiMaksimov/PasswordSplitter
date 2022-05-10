OBJS	= main.o
SOURCE	= main.cpp
HEADER	= rng.h bigint.h
OUT	= password
CC	 = g++
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
