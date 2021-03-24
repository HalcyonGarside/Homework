bank_server : bank request_queue
	gcc -o bank_server.o bank_server.c Bank.o request_queue.o -lpthread

bank : Bank.c Bank.h
	gcc Bank.c -c

request_queue : request_queue.c request_queue.h
	gcc request_queue.c -c
