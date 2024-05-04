CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g -gdwarf-4
LDFLAGS = -lm
OBJS = tsp.o stack.o graph.o path.o
EXEC = tsp

all : tsp

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o : %.c 
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(EXEC) $(OBJS)
	
format: 
	clang-format -i --style=file *.[ch]
	
scan-build: clean
	scan-build --use-cc$(CC) make
