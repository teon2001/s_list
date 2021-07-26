build: main

list.o: d_list.c list.h
	gcc -c d_list.c -o list.o -g

# stack.o: stack.c stack.h list.h
# 	gcc -c stack.c -o stack.o

# queue.o: queue.c queue.h list.h
# 	gcc -c queue.c -o queue.o

# hashtable.o: list.h hashtable.c hashtable.h
# 	gcc -c hashtable.c -o hashtable.o

tester.o: tester.c list.h tester.h
	gcc -c tester.c -o tester.o


main.o: list.h main.c tester.h
	gcc -c main.c -o main.o

main: main.o list.o tester.o
	gcc main.o list.o tester.o -o main 
#hashtable.o 

clean:
	rm main *.o