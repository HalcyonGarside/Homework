#include "request_queue.h"
#include <stdlib.h>

queue* make_queue()
{
	request* head = (request*)malloc(sizeof(request));
	queue* q = (queue*)malloc(sizeof(queue));
	q->head = head;
	q->tail = head;
	q->size = 0;
	return q;
}

int add_req(queue* q, request* req)
{
	q->tail->next = req;
	q->tail = req;

	q->size++;
	return q->size;
}

request* remove_req(queue* q)
{
	request* ret = q->head->next;
	q->head->next = ret->next;

	q->size--;
	return ret;
}
