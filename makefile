CUNIT_INC := -I/usr/local/include/CUnit/ 
ALG_INC   := -I/home/zuweie/WorkShop/code/Algorithms/algorithms/
LIB       := -L/usr/local/lib/ 

BIN=/home/zuweie/WorkShop/code/Algorithms/out
CC=gcc

VPATH = algorithms test_case
 
test_sort : test_sort.o sort.o my_tool.o
	$(CC) $^ $(CUNIT_INC) $(LIB) -D SORT_DEBUG -lcunit -o $(BIN)/$@

test_sort.o : test_sort.c kv.h sort.h my_tool.h
	$(CC) $(ALG_INC) -c $<

sort.o : sort.c sort.h kv.h
	$(CC) -c $<

my_tool.o : my_tool.c my_tool.h
	$(CC) -c $<

clean:
	rm -f *.o *~  algorithms/*.*~ test_case/*.*~ out/*  
