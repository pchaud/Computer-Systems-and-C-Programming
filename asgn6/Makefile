CC=clang
CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g -gdwarf-4
LDFLAGS=-lm
OBJS=huff.o bitwriter.o node.o pq.o
PQ_OBJ=pq.o node.o
NO_OBJ=node.o
BW_OBJ=bitwriter.o
EXEC=huff
EXEC_PQ=pqtest
EXEC_NO=nodetest
EXEC_BW=bwtest
LIBS1=io-$(shell uname -m).a

all : huff pqtest nodetest bwtest

$(EXEC) : $(OBJS) $(LIBS1)
	$(CC) $(CFLAGS) -o $@ $^
	
$(EXEC_PQ) : $(PQ_OBJ) pqtest.o
	$(CC) $(CFLAGS) -o $@ $^ 
		
$(EXEC_NO) : $(NO_OBJ) nodetest.o
	$(CC) $(CFLAGS) -o $@ $^ 
		
$(EXEC_BW) : $(BW_OBJ) $(LIBS1) bwtest.o 
	$(CC) $(CFLAGS) -o $@ $^ 
	
%.o : %.c 
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(EXEC) $(EXEC_PQ) $(EXEC_NO) $(EXEC_BW) $(OBJS) pqtest.o nodetest.o bwtest.o
	
format: 
	clang-format -i --style=file *.[ch]
	
scan-build: clean
	scan-build --use-cc$(CC) make
		
