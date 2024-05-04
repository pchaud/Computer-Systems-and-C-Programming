CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g -gdwarf-4
LDFLAGS = -lm
OBJS = colorb.o io.o bmp.o 
OBJ = io.o
EXEC = colorb
EXEC_IO = iotest

all : colorb iotest

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
$(EXEC_IO) : $(OBJ) iotest.o
	$(CC) $(CFLAGS) -o $@ $^ 
		
%.o : %.c 
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(EXEC) $(EXEC_IO) $(OBJS) iotest.o
	
format: 
	clang-format -i --style=file *.[ch]
	
scan-build: clean
	scan-build --use-cc$(CC) make
