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

/*******************/
/* Include Section */
/*******************/
#include <pthread.h>

/*******************/
/* Defines Section */
/*******************/

/*
 * @brief A macro to enable or disable debug messages.
 * @note Set this macro to 1 to enable debug messages, or 0 to disable them.
 * @note This macro is used for the user's convenience.
 */
#define DEBUG_MESSAGES 0

/*
 * @brief Define the maximum size of the queue.
 * @note The default maximum size of the queue is 10000 nodes.
 */
#define QUEUE_MAX_SIZE 10000


/***********************************/
/* Structure Declaratios Section */
/***********************************/

/*
 * @brief A cyclic queue structure.
 * @param data An array to store the data.
 * @param front The index of the front of the queue.
 * @param rear The index of the rear of the queue.
 * @param size The size of the queue.
 * @param lock A mutex to lock the queue.
 * @param full A condition variable to signal when the queue is full.
 * @param empty A condition variable to signal when the queue is empty.
 * @note The queue is cyclic, so the rear of the queue can be before the front of the queue.
 * @note The queue is thread-safe, so it can be used by multiple threads simultaneously.
 * @warning Don't access the queue directly, use the provided functions instead.
 * @attention This queue is using monitors to synchronize the threads, never access any of the elements or the structure directly.
*/
typedef struct _Queue {

	/*
	 * @brief An array to store the data, in integer format.
	 * @note The data is stored in a cyclic manner.
	 * @note The front of the queue is the first element in the array.
	 * @note The rear of the queue is the last element in the array.
	 * @warning Don't access the data directly, use the provided functions instead.
	 */
	int data[QUEUE_MAX_SIZE];

	/*
	 * @brief The index of the front of the queue.
	 * @warning Don't access the front directly, use the provided functions instead.
	 */
	int front;

	/*
	 * @brief The index of the rear of the queue.
	 * @warning Don't access the rear directly, use the provided functions instead.
	 */
	int rear;

	/*
	 * @brief The size of the queue.
	 * @note The size of the queue is the number of nodes in it.
	 * @warning Don't access the size directly, query it using queueSize() instead.
	 */
	int size;

	/*
	 * @brief A mutex to lock the queue.
	 * @note The queue is thread-safe, so it can be used by multiple threads simultaneously.
	 * @warning Don't access this lock and don't lock the queue directly.
	 */
	pthread_mutex_t lock;

	/*
	 * @brief A condition variable to signal when the queue is full.
	 * @note This condition variable is used to signal the producer threads when the queue is full.
	 * @warning Don't access this condition variable, and never signal it directly.
	 */
	pthread_cond_t full;

	/*
	 * @brief A condition variable to signal when the queue is empty.
	 * @note This condition variable is used to signal the consumer threads when the queue is empty.
	 * @warning Don't access this condition variable, and never signal it directly.
	 */
	pthread_cond_t empty;
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
	* @return The data at the head of the queue on success, -1 if the queue is empty or an error occurred.
	* @note This function isn't a part of the assignment, but I added it for debugging purposes.
	* @warning Do not use this function to dequeue data from the queue,
	* 			as it does not dequeue the data, it only returns it.
	*/
	int queuePeek(PQueue queue);

	/*
	* @brief Peeks at the data at the tail of the queue.
	* @param queue A pointer to the queue to peek at.
	* @return The data at the tail of the queue on success, -1 if the queue is empty or an error occurred.
	* @note This function isn't a part of the assignment, but I added it for debugging purposes.
	* @warning Don't try to use this function to dequeue data from the queue like it's a stack,
	* 			as it does not dequeue the data, it only returns it.
	*/
	int queuePeekTail(PQueue queue);

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