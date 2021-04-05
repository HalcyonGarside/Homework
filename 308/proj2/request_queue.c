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
	q->tail->next = req;
	//req->next = q->head->next;
	//q->head->next = req;
	q->tail = req;

	q->size++;
	//printf("%d\n", q->size);
	//if(q->size == 1) q->tail = req;
	return q->size;
}

request* remove_req(queue* q)
{
	//If nothing in queue, return null
	if(q->head->next == NULL) return NULL;
		
	//printf("the head is fine\n");
	//char* debg = (char*)malloc(10 * sizeof(char));
	//Reduce queue size
	q->size--;
	//printf("size: %d\n", q->size);
	//fgets(debg, 10, stdin);

	//Return the top of the queue.
	request* ret = q->head->next;
	q->head->next = q->head->next->next;

	if(q->head->next == NULL)
		q->tail = q->head;

	//Put the tail where the top of the queue is
	//q->tail = q->head;
	//while(q->tail->next != ret)
		//q->tail = q->tail->next;

	return ret;
}
