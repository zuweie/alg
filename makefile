CUNIT_INC := -I/usr/local/include/CUnit/ 
ALG_INC   := -I/home/zuweie/WorkShop/code/Algorithms/algorithms/
LIB       := -L/usr/local/lib/ 
CFLAG     := -g 
BIN=/home/zuweie/WorkShop/code/Algorithms/out
CC=gcc

VPATH = algorithms test_case
 
test_alg : test_alg.o sort.o heap.o my_select.o my_tool.o
	$(CC) $(CFLAG)  $^ $(CUNIT_INC) $(LIB) -lcunit -lm -o $(BIN)/$@

test_alg.o : test_alg.c kv.h sort.h heap.h my_select.h my_tool.h 
	$(CC) $(ALG_INC) $(CFLAG) -c $<

sort.o : sort.c sort.h kv.h
	$(CC) $(CFLAG) -c $<

heap.o : heap.c heap.h kv.h
	$(CC) $(CFLAG) -c $<

my_select.o : my_select.c my_select.h
	$(CC) $(CFLAG) -c $<

my_tool.o : my_tool.c my_tool.h
	$(CC) $(CFLAG) -c $<

clean:
	rm -f *.o *~  algorithms/*.*~ test_case/*.*~ out/*  
