#include "../include/Queue.h"
#include <stdio.h>
#include <stdlib.h>

PQueue queueCreate() {
	PQueue queue = (PQueue)malloc(sizeof(Queue));

	if (queue == NULL)
	{
		fprintf(stderr, "queueCreate() failed: malloc() failed\n");
		return NULL;
	}

	queue->front = 0;
	queue->rear = -1;
	queue->size = 0;

	if (pthread_mutex_init(&queue->lock, NULL) != 0)
	{
		fprintf(stderr, "queueCreate() failed: pthread_mutex_init() failed\n");
		free(queue);
		return NULL;
	}

	if (pthread_cond_init(&queue->full, NULL) != 0)
	{
		fprintf(stderr, "queueCreate() failed: pthread_cond_init() failed\n");
		MUTEX_DESTROY(&queue->lock);
		free(queue);
		return NULL;
	}

	if (pthread_cond_init(&queue->empty, NULL) != 0)
	{
		fprintf(stderr, "queueCreate() failed: pthread_cond_init() failed\n");
		MUTEX_DESTROY(&queue->lock);
		COND_DESTROY(&queue->full);
		free(queue);
		return NULL;
	}

	return queue;
}

void queueDestroy(PQueue queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueDestroy() failed: queue is NULL\n");
		return;
	}

	MUTEX_LOCK(&queue->lock);

	MUTEX_DESTROY(&queue->lock);
	COND_DESTROY(&queue->full);
	COND_DESTROY(&queue->empty);

	free(queue);
}

void queueEnqueue(PQueue queue, int data) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueEnqueue() failed: queue is NULL\n");
		return;
	}

	MUTEX_LOCK(&queue->lock);

	while (queue->size == QUEUE_MAX_SIZE)
		COND_WAIT(&queue->full, &queue->lock);

	queue->rear = (queue->rear + 1) % QUEUE_MAX_SIZE;
	queue->data[queue->rear] = data;
	queue->size++;

	COND_SIGNAL(&queue->empty);
	MUTEX_UNLOCK(&queue->lock);
}

int queueDequeue(PQueue queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueDequeue() failed: queue is NULL\n");
		return -1;
	}

	MUTEX_LOCK(&queue->lock);

	while (queue->size == 0)
		COND_WAIT(&queue->empty, &queue->lock);

	int data = queue->data[queue->front];
	queue->front = (queue->front + 1) % QUEUE_MAX_SIZE;
	queue->size--;

	COND_SIGNAL(&queue->full);
	MUTEX_UNLOCK(&queue->lock);

	return data;
}

int queueIsEmpty(PQueue queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueIsEmpty() failed: queue is NULL\n");
		return -1;
	}

	MUTEX_LOCK(&queue->lock);
	int isEmpty = (queue->size == 0);
	MUTEX_UNLOCK(&queue->lock);

	return isEmpty;
}

#if DEBUG_MESSAGES == 1
	int queueSize(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queueSize() failed: queue is NULL\n");
			return -1;
		}

		MUTEX_LOCK(&queue->lock);
		int size = queue->size;
		MUTEX_UNLOCK(&queue->lock);

		return size;
	}

	int queuePeek(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queuePeek() failed: queue is NULL\n");
			return -1;
		}

		MUTEX_LOCK(&queue->lock);

		if (queue->size == 0)
		{
			MUTEX_UNLOCK(&queue->lock);
			return -1;
		}

		int data = queue->data[queue->front];

		MUTEX_UNLOCK(&queue->lock);

		return data;
	}

	int queuePeekTail(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queuePeekTail() failed: queue is NULL\n");
			return -1;
		}

		MUTEX_LOCK(&queue->lock);

		if (queue->size == 0)
		{
			MUTEX_UNLOCK(&queue->lock);
			return -1;
		}

		int data = queue->data[queue->rear];

		MUTEX_UNLOCK(&queue->lock);

		return data;
	}

	void queuePrint(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queuePrint() failed: queue is NULL\n");
			return;
		}

		MUTEX_LOCK(&queue->lock);

		fprintf(stdout, "Queue info:\n[\n");
		fprintf(stdout, "\tQueue: %p\n", (void *)queue);
		fprintf(stdout, "\tQueue size: %d\n", queue->size);
		fprintf(stdout, "\tQueue front: %d\n", queue->front);
		fprintf(stdout, "\tQueue rear: %d\n", queue->rear);
		fprintf(stdout, "\tQueue lock: %p\n", (void *)&queue->lock);
		fprintf(stdout, "\tQueue full cond: %p\n", (void *)&queue->full);
		fprintf(stdout, "\tQueue empty cond: %p\n", (void *)&queue->empty);
		fprintf(stdout, "\tQueue nodes:\n\t\t");

		if (queue->size == 0)
		{
			fprintf(stdout, "NULL\n]\n");
			MUTEX_UNLOCK(&queue->lock);
			return;
		}

		int i = queue->front;

		fprintf(stdout, "%d", queue->data[i]);

		for (int j = 1; j < queue->size; j++)
		{
			i = (i + 1) % QUEUE_MAX_SIZE;
			fprintf(stdout, " -> %d", queue->data[i]);
		}

		fprintf(stdout, "\n]\n");

		MUTEX_UNLOCK(&queue->lock);
	}
#endif // DEBUG_MESSAGES