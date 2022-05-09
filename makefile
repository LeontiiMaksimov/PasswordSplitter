OBJS	= main.o
SOURCE	= main.cpp
HEADER	= bigint.h rng.h
OUT	= password_manager
LFLAGS	 = 

all: password_manager

password_manager: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)
