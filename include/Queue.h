/*
 *  Advanced Programming Course Assignment 2
 *  Queue header file
 *  Copyright (C) 2024  Roy Simanovich and Almog Shor
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _QUEUE_H
#define _QUEUE_H

#include <pthread.h>

/*
 * @brief A macro to enable or disable debug messages.
 * @note Set this macro to 1 to enable debug messages, or 0 to disable them.
 * @note This macro is used for the user's convenience.
*/
#define DEBUG_MESSAGES 0


/******************************/
/* Struct Definitions Section */
/******************************/

/*
 * @brief A queue node struct.
 * @param data The data stored in the node, in integer form.
 * @param next The next node in the queue.
 * @note This struct is used to store data in the queue internally, and is not meant to be used by the user.
 * @warning Messing with this struct can cause the queue to malfunction and/or undefined behavior.
*/
typedef struct _QueueNode {
	/*
	 * @brief The data stored in the node, in integer form.
	 * @note Represented as an integer, as the assignment requires the queue to store integers only.
	 * @attention Optimized for the assignment.
	*/
	int data;

	/*
	 * @brief The next node in the queue.
	 * @note This is a pointer to a QueueNode struct, which is a singly-linked list, so the next node is the next node in the queue.
	 * @warning Never try to access the next node directly, as it can cause the queue to malfunction and/or undefined behavior.
	*/
	struct _QueueNode *next;
} QueueNode, *PQueueNode;

/*
 * @brief A queue struct that holds the head, tail, size, lock of the queue for thread-safety, and a condition variable for blocking.
 * @param head The head of the queue.
 * @param tail The tail of the queue.
 * @param size The number of nodes in the queue.
 * @param lock A mutex lock for the queue, to make the queue thread-safe.
 * @param cond A condition variable for the queue, to make the queue a blocking queue.
 * @note This struct is used to represent the queue itself.
 * @warning Always use the functions provided to access the queue, and never try to access it directly.
*/
typedef struct _Queue {

	/*
	 * @brief The head of the queue.
	 * @note This is a pointer to a QueueNode struct, which is an internal struct used to store data in the queue.
	 * @note The QueueNode struct is a singly-linked list, so the head is the first node in the queue.
	*/
	PQueueNode head;

	/*
	 * @brief The tail of the queue, for faster enqueueing (O(1) instead of O(n)).
	 * @note This is a pointer to a QueueNode struct, which is an internal struct used to store data in the queue.
	 * @note The QueueNode struct is a singly-linked list, so the tail is the last node in the queue,
	 * 			and thus the lastest node to be enqueued.
	*/
	PQueueNode tail;

	/*
	 * @brief The number of nodes in the queue.
	 * @note This is an unsigned integer, and thus theoretically can hold 4,294,967,295 nodes.
	*/
	unsigned int size;

	/*
	 * @brief A mutex lock for the queue, to make the queue thread-safe so that multiple threads can access it at the same time.
	 * @note When a thread wants to access the queue, it must first lock it.
	 * @note When a thread is done accessing the queue, it must unlock it.
	 * @note This feature requires the use of the pthread library, so make sure to link it when compiling.
	*/
	pthread_mutex_t lock;

	/*
	 * @brief A condition variable for the queue, to make the queue a blocking queue, so that threads can wait for it to be non-empty.
	 * @note When a thread dequeues from an empty queue, it will wait for the queue to be non-empty.
	 * @note When a thread enqueues to an empty queue, it will signal the condition variable to wake up the waiting thread.
	 * @note This feature requires the use of the pthread library, so make sure to link it when compiling.
	*/
	pthread_cond_t cond;
} Queue, *PQueue;


/********************************/
/* Function Declaratios Section */
/********************************/

/*
 * @brief Creates a new queue.
 * @return A pointer to the new queue on success, NULL otherwise.
 * @note The user is responsible for freeing the memory of the queue with queueDestroy().
*/
PQueue queueCreate();

/*
 * @brief Destroys a queue.
 * @param queue A pointer to the queue to destroy.
 * @attention If the queue is destoryed while it is not empty, the data stored in it will be lost forever.
 * @return void
*/
void queueDestroy(PQueue queue);

/*
 * @brief Enqueues data to the queue.
 * @param queue A pointer to the queue to enqueue to.
 * @param data Integer data to enqueue.
 * @return void
*/
void queueEnqueue(PQueue queue, int data);

/*
 * @brief Dequeues data from the queue.
 * @param queue A pointer to the queue to dequeue from.
 * @return integer data on success, -1 if the queue is empty or an error occurred.
*/
int queueDequeue(PQueue queue);

/*
 * @brief Checks if the queue is empty.
 * @param queue A pointer to the queue to check.
 * @return 1 if the queue is empty, 0 if it is not, -1 if an error occurred.
*/
int queueIsEmpty(PQueue queue);

/*
 * @brief Gets the size of the queue.
 * @param queue A pointer to the queue to get the size of.
 * @return The size of the queue on success, -1 if an error occurred.
 * @note The size of the queue is the number of nodes in it.
 * @attention Do not confuse the size of the queue with the size of the data stored in it.
*/
int queueSize(PQueue queue);

#if DEBUG_MESSAGES == 1
	/*
	* @brief Peeks at the data at the head of the queue.
	* @param queue A pointer to the queue to peek at.
	* @return A pointer to the data at the head of the queue on success,
	* 			NULL if the queue is empty or an error occurred.
	* @note This function isn't a part of the assignment, but I added it for debugging purposes.
	* @warning Do not use this function to dequeue data from the queue,
	* 			as it does not dequeue the data, it only returns a pointer to it.
	* @warning Do not free the data returned by this function, as it is still in the queue.
	*/
	void *queuePeek(PQueue queue);

	/*
	* @brief Peeks at the data at the tail of the queue.
	* @param queue A pointer to the queue to peek at.
	* @return A pointer to the data at the tail of the queue on success,
	* 			NULL if the queue is empty or an error occurred.
	* @note This function isn't a part of the assignment, but I added it for debugging purposes.
	* @warning Don't try to use this function to dequeue data from the queue like it's a stack,
	* 			as it does not dequeue the data, it only returns a pointer to it, and the queue is not a stack.
	* @warning Do not free the data returned by this function, as it is still in the queue.
	*/
	void *queuePeekTail(PQueue queue);

	/*
	 * @brief Prints the queue to the standard output.
	 * @param queue A pointer to the queue to print.
	 * @return void
	 * @note This function isn't a part of the assignment, but I added it for debugging purposes.
	*/
	void queuePrint(PQueue queue);

#endif // DEBUG_MESSAGES == 1


/******************/
/* Macros Section */
/******************/

/*
 * @brief A macro to enqueue data to the queue.
 * @param queue A pointer to the queue to enqueue to.
 * @param data The data to enqueue.
 * @note This macro is used for the user's convenience.
*/
#define ENQUEUE(queue, data) queueEnqueue(queue, data)

/*
 * @brief A macro to dequeue data from the queue.
 * @param queue A pointer to the queue to dequeue from.
 * @return The dequeued data on success, -1 if the queue is empty or an error occurred.
 * @note This macro is used for the user's convenience.
*/
#define DEQUEUE(queue) queueDequeue(queue)

#if DEBUG_MESSAGES == 1
	/*
	 * @brief Debug: A macro to peek at the data at the head of the queue.
	 * @param queue A pointer to the queue to peek at.
	 * @return The data at the head of the queue on success, -1 if the queue is empty or an error occurred.
	 * @note This macro is used for the user's convenience.
	 * @note This macro is not a part of the assignment, but I added it for debugging purposes.
	*/
	#define PEEK(queue) queuePeek(queue)

	/*
	 * @brief Debug: A macro to peek at the data at the tail of the queue.
	 * @param queue A pointer to the queue to peek at.
	 * @return The data at the head of the queue on success, -1 if the queue is empty or an error occurred.
	 * @note This macro is used for the user's convenience.
	 * @note This macro is not a part of the assignment, but I added it for debugging purposes.
	*/
	#define PEEK_TAIL(queue) queuePeekTail(queue)
#endif // DEBUG_MESSAGES


/*
 * @brief A macro to initialize a mutex.
 * @param mutex A pointer to the mutex to initialize.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define MUTEX_INIT(mutex) pthread_mutex_init(mutex, NULL)

/*
 * @brief A macro to lock a mutex.
 * @param mutex A pointer to the mutex to lock.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define MUTEX_LOCK(mutex) pthread_mutex_lock(mutex)

/*
 * @brief A macro to unlock a mutex.
 * @param mutex A pointer to the mutex to unlock.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define MUTEX_UNLOCK(mutex) pthread_mutex_unlock(mutex)

/*
 * @brief A macro to destroy a mutex.
 * @param mutex A pointer to the mutex to destroy.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define MUTEX_DESTROY(mutex) pthread_mutex_destroy(mutex)

/*
 * @brief A macro to initialize a condition variable.
 * @param cond A pointer to the condition variable to initialize.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define COND_INIT(cond) pthread_cond_init(cond, NULL)

/*
 * @brief A macro to wait on a condition variable.
 * @param cond A pointer to the condition variable to wait on.
 * @param mutex A pointer to the mutex to lock while waiting on the condition variable.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define COND_WAIT(cond, mutex) pthread_cond_wait(cond, mutex)

/*
 * @brief A macro to signal a condition variable.
 * @param cond A pointer to the condition variable to signal.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
 * @attention I've used pthread_cond_broadcast() instead of pthread_cond_signal() for optimization purposes.
*/
#define COND_SIGNAL(cond) pthread_cond_broadcast(cond)

/*
 * @brief A macro to destroy a condition variable.
 * @param cond A pointer to the condition variable to destroy.
 * @return 0 on success, or an error code on failure.
 * @note This macro is used for the user's convenience.
*/
#define COND_DESTROY(cond) pthread_cond_destroy(cond)


#endif // _QUEUE_H