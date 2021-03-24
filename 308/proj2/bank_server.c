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

//The output file being written to
FILE* outfile;

//The worker threads
pthread_t* workers;

//The requests queue
queue* requests;

//delims for strtok
const char delim[4] = " \n";


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
	//Check correct number of program arguments
	if(argc < 4)
	{
		printf("Insufficient arguments. \nTo start the server: ./appserver <# of worker threads> <# of accounts> <output file>\n");
		return 0;
	}

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

	//Initialize bank accounts
	num_accs = atoi(argv[2]);
	initialize_accounts(num_accs);

	//Initialize output file
	outfile = fopen(argv[3], "w");
	if(outfile == NULL)
	{
		printf("Could not open the output file!  Aborting...\n");
		return 0;
	}

	//Initialize request queue
	requests = make_queue();
	int cur_id = 0;

	//This was a test.  Ignore me until something goes arye.
	//fprintf(outfile, "Hey ;3");

	//Initialize input and token strings
	char* input = (char*)malloc(200 * sizeof(char));
	char* tok = (char*)malloc(50 * sizeof(char));
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

			//Build and add request
			request* req = (request*)malloc(sizeof(request));
			req->request_id = cur_id;
			req->check_acc_id = accnum;
			req->transfers = NULL;
			req->num_transfers = 0;

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

void* worker_thread(void* args)
{
}

void capitalize(char* string)
{
	int length = strlen(string);
	for(int i = 0; i < length; i++)
	{
		string[i] = toupper(string[i]);
	}
}
