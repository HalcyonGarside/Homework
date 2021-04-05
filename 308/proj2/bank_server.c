/*
 * bank_server.c
 * Author: William Blanchard
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "Bank.h"
#include "request_queue.h"

/*
 * ----------GLOBAL VARIABLES----------
 */

//Number of threads being used by the program
int num_threads;

//Number of accounts being kept track of
int num_accs;

//Sorta like bathroom passes, but for accounts!
//(account mutexes for one-at-a-time account access)
pthread_mutex_t* acc_passes;

pthread_mutex_t q_pass;

//The output file being written to
FILE* outfile;

//The worker threads
pthread_t* workers;

//The requests queue
queue* requests;

//delims for strtok
const char delim[4] = " \n";

//Debug string for breakpoints
char* debg;

//Time value
struct timespec tm;

//Tells how many threads are currently running
int running;


/*
 * ----------PROTOTYPES----------
 */

//The function each thread will be working with
void* worker_thread(void* args);

/*
 * The helper function to capitalize all characters in a string
 *
 * @param string - the string to capitalize
 */
void capitalize(char* string);


/*
 * ----------FUNCTION DEFINITIONS----------
 */

//The main thread function, looping.
int main(int argc, char* argv[])
{
	//Initialize debug string
	debg = (char*)(10 * sizeof(char));

	//Check correct number of program arguments
	if(argc < 4)
	{
		printf("Insufficient arguments. \nTo start the server: ./appserver <# of worker threads> <# of accounts> <output file>\n");
		return 0;
	}
	
	//Initialize bank accounts
	num_accs = atoi(argv[2]);
	if(num_accs == 0)
	{
		printf("Invalid argument for number of bank accounts\n");
		return 0;
	}
	initialize_accounts(num_accs);

	//Initialize queue and mutexes
	running = 0;
	requests = make_queue();
	acc_passes = (pthread_mutex_t*)malloc(num_accs * sizeof(pthread_mutex_t));
	for(int i = 0; i < num_accs; i++)
		pthread_mutex_init(&acc_passes[i], NULL);
	pthread_mutex_init(&q_pass, NULL);

	//Initialize worker threads
	num_threads = atoi(argv[1]);
	workers = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
	if(workers == NULL)
	{
		printf("Invalid argument for number of worker threads\n");
		return 0;
	}
	for(int i = 0; i < num_threads; i++)
	{

		pthread_create(&workers[i], NULL, worker_thread, NULL);
	}

	//Initialize output file
	outfile = fopen(argv[3], "w");
	if(outfile == NULL)
	{
		printf("Could not open the output file!  Aborting...\n");
		return 0;
	}

	//Initialize account mutexes
	//acc_passes = (pthread_mutex_t*)malloc(num_accs * sizeof(pthread_mutex_t));

	//Initialize ID counter
	int cur_id = 0;

	//This was a test.  Ignore me until something goes arye.
	//fprintf(outfile, "Hey ;3");

	//Initialize input and token strings
	char* input = (char*)malloc(200 * sizeof(char));
	char* tok = (char*)malloc(50 * sizeof(char));

	//Initialize time variable
	struct timeval stime, etime;

	while(1)
	{
		//Grab command
		printf(">");
		fgets(input, 200, stdin);

		//Find main command name, capitalize it
		tok = strtok(input, delim);
		capitalize(tok);

		//If the request is to check an account
		if(strcmp(tok, "CHECK") == 0)
		{
			int accnum = atoi(strtok(NULL, delim));

			//Check for valid argument
			if(accnum > num_accs || accnum <= 0)
			{
				printf("%d IS AN INVALID ACCOUNT NUMBER.\n ACCOUNT NUMBER MUST BE A NONZERO NUMBER LESS THAN OR EQUAL TO THE NUMBER OF ACCOUNTS\n", accnum);
				continue;
			}
			
			//Increment current id
			cur_id++;
			printf("< ID %d\n", cur_id);

			//Get and record time
			//gettimeofday(&stime, NULL);
			//printf("%ld.%06ld\n", time.tv_sec, time.tv_usec); //DEBUGDEBUGDEBUG

			//Build and add request
			request* req = (request*)malloc(sizeof(request));
			req->request_id = cur_id;
			req->check_acc_id = accnum;
			req->transfers = NULL;
			req->num_transfers = 0;
			clock_gettime(CLOCK_REALTIME, &tm);
			req->starttime = tm;

			add_req(requests, req);
			running++;
		}
		
		//If the request was to transfer money
		else if(strcmp(tok, "TRANS") == 0)
		{
			//Build the array of transfers
			transfer* transfers = (transfer*)malloc(10 * sizeof(transfer));
			int transfer_num = 0;
			int err = 0;
			while(transfer_num < 10 && (tok = strtok(NULL, delim)) != NULL)
			{
				//Get the account id
				transfer this_trans;
				this_trans.acc_id = atoi(tok);

				//If the account number is invalid, throw an error
				if(this_trans.acc_id > num_accs || this_trans.acc_id <= 0)
				{
					printf("INVALID ACC NUMBER.  ABORTING...\n");
					err = 1;
					break;
				}
				
				//If the number of numbers in the request is not even (all ops should be in pairs), throw an error
				if((tok = strtok(NULL, delim)) == NULL)
				{
					printf("UNEVEN NUMBER OF INTEGER VALUES.  ABORTING...\n");
					err = 1;
					break;
				}
				
				//If all succeeds, associate this amount with this transfer and add it to the transfers array
				this_trans.amount = atoi(tok);

				//Debug
				//printf("Acc %d, Amt: %d", this_trans.acc_id, this_trans.amount);

				transfers[transfer_num] = this_trans;
				transfer_num++;
			}
			//Don't make the request if there was an error
			if(err > 0)
				continue;

			//Build and add request
			cur_id++;
			printf("< ID %d\n", cur_id);

			request* req = (request*)malloc(sizeof(request));
			req->request_id = cur_id;
			req->check_acc_id = 0;
			req->transfers = transfers;
			req->num_transfers = transfer_num;
			clock_gettime(CLOCK_REALTIME, &tm);
			req->starttime = tm;

			add_req(requests, req);

			running++;
		}

		else if(strcmp(tok, "END") == 0)
		{
			printf("Ending process...\n");
		//	printf("%d\n", running);
			while(running > 0)
			{
		//		printf("%d\n", running);
			}
			printf("Process ended. \n");
			break;
		}

		else
		{
			printf("Valid commands are CHECK, TRANS, and END\n");
		}
	}

	//Cleanup
	free_accounts();
	fclose(outfile);
	return 1;
}

// transfer qsort function
int transaction_sort(const void * a, const void * b)
{
	return (((transfer*)a)->acc_id - ((transfer*)b)->acc_id);
}

void* worker_thread(void* args)
{
	//Initialize thread variables
	int loop;
	//running++;
	request* this_req = NULL;

	while(1)
	{
		loop = 0;

		//While a request hasn't been acquired yet
		while(this_req == NULL) 
		{
			//Acquire the queue pass and grab a request if one's available
			pthread_mutex_lock(&q_pass);
			this_req = remove_req(requests);
			pthread_mutex_unlock(&q_pass);

			//If the loop hasn't looped yet and there isn't another request, the thread isn't running
			//if(this_req == NULL && loop == 0)
			//{
			//	running--;
			//	loop = 1;
			//	printf("%d\n", running);
			//}
		}
		
		//If the while loop looped, the running count lowered, so increase it again
		//if(loop == 1)
			//running++;
		
		//If somehow the request is null, bypass all operations
		if(this_req == NULL) continue;
		
		//If we are checking an account's balance
		if(this_req->check_acc_id != 0)
		{
			//Lock account mutex, get the balance and current time, then unlock the mutex
			pthread_mutex_lock(&acc_passes[this_req->check_acc_id - 1]);
			int accbal = read_account(this_req->check_acc_id);
			clock_gettime(CLOCK_REALTIME, &tm);
			this_req->endtime = tm;
	
			fprintf(outfile, "%d BAL %d TIME %ld.%06ld %ld.%06ld\n", this_req->request_id,
					accbal,
					this_req->starttime.tv_sec,
					this_req->starttime.tv_nsec / 1000,
					this_req->endtime.tv_sec,
					this_req->endtime.tv_nsec / 1000);
			pthread_mutex_unlock(&acc_passes[this_req->check_acc_id - 1]);
			
		}
		//If we are making a transfer
		else
		{
			//Acquire all transfers and sort them according to account id
			transfer* transfers = this_req->transfers;
			qsort(transfers, this_req->num_transfers, sizeof(transfer), transaction_sort);
			
			//Lock all needed mutexes	
			for(int i = 0; i < this_req->num_transfers; i++)
			{
				int accnum = transfers[i].acc_id;
				pthread_mutex_lock(&acc_passes[accnum - 1]);
			}
	
			//Get all of the results from the transactions
			int* results = (int*)malloc(this_req->num_transfers * sizeof(int));
			int  bad_trans = 0;
			for(int i = 0; i < this_req->num_transfers; i++)
			{
				results[i] = read_account(transfers[i].acc_id) + transfers[i].amount;
				if(results[i] < 0)
				{
					bad_trans = transfers[i].acc_id;
					break;
				}
			}
			
			//If a bad transaction was run into, say insufficient funds and return
			if(bad_trans != 0)
			{
				clock_gettime(CLOCK_REALTIME, &tm);
				this_req->endtime = tm;
				fprintf(outfile, "%d ISF %d TIME %ld.%06ld %ld.%06ld\n", this_req->request_id,
						bad_trans,
						this_req->starttime.tv_sec,
						this_req->starttime.tv_nsec / 1000,
						this_req->endtime.tv_sec,
						this_req->endtime.tv_nsec / 1000);
			}
	
			//Otherwise, assign all of the results and say the transaction went well
			else
			{
				for(int i = 0; i < this_req->num_transfers; i++)
					write_account(transfers[i].acc_id, results[i]);
	
				clock_gettime(CLOCK_REALTIME, &tm);
				this_req->endtime = tm;
				fprintf(outfile, "%d OK TIME %ld.%06ld %ld.%06ld\n", this_req->request_id,
						this_req->starttime.tv_sec,
						this_req->starttime.tv_nsec / 1000,
						this_req->endtime.tv_sec,
						this_req->endtime.tv_nsec / 1000);
			}

			//Unlock all mutexes associated with this transfer	
			for(int i = 0; i < this_req->num_transfers; i++)
			{
				pthread_mutex_unlock(&acc_passes[transfers[i].acc_id - 1]);
			}
		}

		running--;
		this_req = NULL;
	}
}

void capitalize(char* string)
{
	int length = strlen(string);
	for(int i = 0; i < length; i++)
	{
		string[i] = toupper(string[i]);
	}
}
