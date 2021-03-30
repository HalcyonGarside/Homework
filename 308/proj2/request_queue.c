#include "request_queue.h"
#include <stdlib.h>

queue* make_queue()
{
	request* head = (request*)malloc(sizeof(request));
	head->next = NULL;

	queue* q = (queue*)malloc(sizeof(queue));
	q->head = head;
	q->tail = head;
	q->size = 0;
	return q;
}

int add_req(queue* q, request* req)
{
	req->next = q->head->next;
	q->head->next = req;

	q->size++;
	if(q->size == 1)
		q->tail = req;
	return q->size;
}

request* remove_req(queue* q)
{
	//If nothing in queue, return null
	if(q->head == q->tail) return NULL;

	//char* debg = (char*)malloc(10 * sizeof(char));
	//Reduce queue size
	q->size--;
	//printf("size: %d\n", q->size);
	//fgets(debg, 10, stdin);

	//Return the top of the queue.
	request* ret = q->tail;

	//Put the tail where the top of the queue is
	q->tail = q->head;
	for(int i = 0; i < q->size; i++)
		q->tail = q->tail->next;

	return ret;
}
