build: pbb_areseIP valgrind

list.o: s_list.c list.h
	gcc -c -Wall s_list.c -o list.o -g

stack.o: stack.c stack.h list.h
	gcc -c stack.c -o stack.o

queue.o: queue.c queue.h list.h
	gcc -c queue.c -o queue.o

hashtable.o: list.h hashtable.c hashtable.h
	gcc -c -Wall hashtable.c -o hashtable.o

tester_hash.o: tester_hash.c list.h tester_hash.h hashtable.h
	gcc -c -Wall tester_hash.c -o tester_hash.o

tester_list.o: tester_list.c list.h tester_list.h hashtable.h
	gcc -c -Wall tester_list.c -o tester_list.o

pbb_areseIP.o: list.h hashtable.h pbb_areseIP.c
	gcc -c -Wall pbb_areseIP.c -o pbb_areseIP.o

main.o: list.h main.c hashtable.h tester_hash.h
	gcc -c -Wall main.c -o main.o

main: main.o list.o tester_hash.o hashtable.o
	gcc -g -Wall main.o list.o tester_hash.o hashtable.o -o main 

pbb_areseIP: pbb_areseIP.o list.o hashtable.o
	gcc -g -Wall list.o pbb_areseIP.o hashtable.o -o pbb_areseIP 

valgrind:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./pbb_areseIP

clean:
	rm main *.o

