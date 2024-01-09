all: main

FLAGS   := -Wall -O2
OBJS    := rc4.o
HEADERS := rc4.h

main: main.c rc4.o $(HEADERS)
	gcc $(FLAGS) -o $@ $< $(OBJS)

%.o: %.c $(HEADERS)
	gcc $(FLAGS) -c $<

.PHONY: clean
clean:
	@rm -fv *.o main
