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
	acc_passes = (pthread_mutex_t*)malloc(num_accs * sizeof(pthread_mutex_t));

	int cur_id = 0;

	//This was a test.  Ignore me until something goes arye.
	//fprintf(outfile, "Hey ;3");

	//Initialize input and token strings
	char* input = (char*)malloc(200 * sizeof(char));
	char* tok = (char*)malloc(50 * sizeof(char));

	//Initialize time variable
	struct timeval time;

	while(1)
	{
		//Grab command
		printf(">");
		fgets(input, 200, stdin);

		//Find main command name, capitalize it
		tok = strtok(input, delim);
		capitalize(tok);

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
			gettimeofday(&time, NULL);
			//printf("%ld.%06ld\n", time.tv_sec, time.tv_usec); //DEBUGDEBUGDEBUG

			//Build and add request
			request* req = (request*)malloc(sizeof(request));
			req->request_id = cur_id;
			req->check_acc_id = accnum;
			req->transfers = NULL;
			req->num_transfers = 0;
			req->starttime = time;

			add_req(requests, req);
		}

		else if(strcmp(tok, "TRANS") == 0)
		{
			//Build the array of transfers
			transfer* transfers = (transfer*)malloc(10 * sizeof(transfer));
			int transfer_num = 0;
			int err = 0;
			while(transfer_num < 10 && (tok = strtok(NULL, delim)) != NULL)
			{
				transfer this_trans;
				this_trans.acc_id = atoi(tok);
				if(this_trans.acc_id > num_accs || this_trans.acc_id <= 0)
				{
					printf("INVALID ACC NUMBER.  ABORTING...\n");
					err = 1;
					break;
				}

				if((tok = strtok(NULL, delim)) == NULL)
				{
					printf("UNEVEN NUMBER OF INTEGER VALUES.  ABORTING...\n");
					err = 1;
					break;
				}
				this_trans.amount = atoi(tok);

				//Debug
				//printf("Acc %d, Amt: %d", this_trans.acc_id, this_trans.amount);

				transfers[transfer_num] = this_trans;
				transfer_num++;
			}
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

			add_req(requests, req);
		}

		else if(strcmp(tok, "END") == 0)
		{
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
	free(tok);
	free(input);
	return 1;
}

// transfer qsort function
int transaction_sort(const void * a, const void * b)
{
	return (((transfer*)a)->acc_id - ((transfer*)b)->acc_id);
}

void* worker_thread(void* args)
{
	request* this_req = NULL;
	while(this_req == NULL) 
	{
		pthread_mutex_lock(&q_pass);
		this_req = remove_req(requests);
		pthread_mutex_unlock(&q_pass);
	};

	if(this_req == NULL) return 0;
	struct timeval endt;

	if(this_req->check_acc_id != 0)
	{
		pthread_mutex_lock(&acc_passes[this_req->check_acc_id - 1]);
		int accbal = read_account(this_req->check_acc_id);
		gettimeofday(&endt, NULL);

		fprintf(outfile, "%d BAL %d TIME %ld.%06ld %ld.%06ld\n", this_req->request_id,
				accbal,
				this_req,
				this_req->starttime.tv_sec,
				this_req->starttime.tv_usec,
				endt.tv_sec,
				endt.tv_usec);
		pthread_mutex_unlock(&acc_passes[this_req->check_acc_id - 1]);
	}
	else
	{
		//Get and sort the array of transfers
		transfer* transfers = this_req->transfers;
		qsort(transfers, this_req->num_transfers, sizeof(transfer), transaction_sort);

		//Acquire mutexes in a fashion that does not cause a deadlock (bc qsort)
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
			gettimeofday(&endt, NULL);
			fprintf(outfile, "%d ISF %d TIME %ld.%06ld %ld.%06ld\n", this_req->request_id,
					bad_trans,
					this_req,
					this_req->starttime.tv_sec,
					this_req->starttime.tv_usec,
					endt.tv_sec,
					endt.tv_usec);
		}

		//Otherwise, assign all of the results and say the transaction went well
		else
		{
			for(int i = 0; i < this_req->num_transfers; i++)
				write_account(transfers[i].acc_id, results[i]);

			gettimeofday(&endt, NULL);
			fprintf(outfile, "%d OK TIME %ld.%06ld %ld.%06ld\n", this_req->request_id,
					this_req,
					this_req->starttime.tv_sec,
					this_req->starttime.tv_usec,
					endt.tv_sec,
					endt.tv_usec);
		}

		for(int i = 0; i < this_req->num_transfers; i++)
		{
			pthread_mutex_unlock(&acc_passes[transfers[i].acc_id - 1]);
		}
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
