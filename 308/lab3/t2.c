/* t2.c
   synchronize threads through mutex and conditional variable 
   To compile use: gcc -o t2 t2.c -lpthread 
*/ 

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* hello();    // define two routines called by threads    
void* world();
void* again();

/* global variable shared by threads */
pthread_mutex_t mutex;  		// mutex
pthread_cond_t done_hello; 	// conditional variable
pthread_cond_t done_world;	// second conditional variable (added)
int done = 0;      	// testing variable

int main (){
    pthread_t tid_hello, tid_world; // thread id
    pthread_t tid_again; // again thread (added)

    /*  initialize mutex and cond variable  */ 
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&done_hello, NULL);
    pthread_cond_init(&done_world, NULL); 
    
    pthread_create(&tid_hello, NULL, hello, NULL); //thread creation
    pthread_create(&tid_world, NULL, world, NULL); //thread creation
    pthread_create(&tid_again, NULL, again, NULL); //again thread creation (added) 

    /* main waits for the two threads to finish */
    pthread_join(tid_hello, NULL);  
    pthread_join(tid_world, NULL);
    pthread_join(tid_again, NULL); //again thread join (added)

    printf("\n");
    return 0;
}

void* hello() {
    pthread_mutex_lock(&mutex);
    printf("hello ");
    fflush(stdout); 	// flush buffer to allow instant print out
    done = 1;
    pthread_cond_signal(&done_hello);	// signal world() thread
    pthread_mutex_unlock(&mutex);	// unlocks mutex to allow world to print
}


void* world() {
    pthread_mutex_lock(&mutex);

    /* world thread waits until done == 1. */
    while(done == 0) 
		pthread_cond_wait(&done_hello, &mutex);

    printf("world");
    fflush(stdout);
    done = 2; //Increment done for again to run (added)
    pthread_cond_signal(&done_world); //Signal that world is finished running (added)
    pthread_mutex_unlock(&mutex); // unlocks mutex

    //I wonder if pthread_mutex_unlock is necessary in hello() or world()
    //since pthread_cond_wait supposedly unlocks the mutex as part of its function.
}

//Added thread function
void* again() {
	while(done < 2)
		pthread_cond_wait(&done_world, &mutex);

	printf(" again");
	fflush(stdout);
	pthread_mutex_unlock(&mutex);
}
