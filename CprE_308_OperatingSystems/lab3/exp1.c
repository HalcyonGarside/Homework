#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//Code for thread t1
void* thread1(void* ptr)
{
	sleep(5);
	printf("Hello from thread 1!\n");
}

//Code for thread t2
void* thread2(void* ptr)
{
	sleep(5);
	printf("Hello from thread 2!\n");
}

int main(int argc, char* argv[])
{
	//Thread declaration
	pthread_t t1, t2;

	//Start function thread1 on thread t1
	pthread_create(&t1, NULL, thread1, NULL);
	//Start function thread2 on thread t2
	pthread_create(&t2, NULL, thread2, NULL);

	//Wait for t1 to finish execution, then wait for t2 to do the same
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Hello from the main thread!\n");

	return 0;
}
