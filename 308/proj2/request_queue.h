#include <stdio.h>
#include <sys/time.h>

/*
 * ----------STRUCTS----------
 */

//Queue types courtesy of the lab doc
typedef struct transfer
{
	int acc_id;		//account ID
	int amount; 		//amount to be added/subtracted (depending on signage)
}transfer;

typedef struct request 
{
	struct request* next;	//pointer to the next request
	int request_id;		//this request ID
	int check_acc_id;	//account ID for a CHECK request
	transfer* transfers; //transfers for a TRANS request
	int num_transfers;	//number of transfers if a TRANS request
	struct timeval starttime, endtime; //start and end times for this request
}request;

typedef struct queue
{
	request* head, * tail; // the head and tail of this queue
	int size; 		//the number of requests in this queue
}queue;

queue* make_queue();

int add_req(queue* q, request* req);

request* remove_req(queue* q);
