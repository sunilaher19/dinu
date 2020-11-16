
CC = g++ -std=c++11
CFLAGS  = -g -Wall

LIBS=		-pthread

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
count:  main.o wk.o wk1.o
	$(CC) $(CFLAGS) -o main main.o wk.o wk1.o $(LIBS)

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
wk.o:  source/wk.cpp include/wk.h
	$(CC) $(CFLAGS) -c source/wk.cpp $(LIBS)

wk1.o:  source/wk1.cpp include/wk1.h
	$(CC) $(CFLAGS) -c source/wk1.cpp $(LIBS)

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o:  source/main.cpp 
	$(CC) $(CFLAGS) -c source/main.cpp include/wk.h include/wk1.h $(LIBS)

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~