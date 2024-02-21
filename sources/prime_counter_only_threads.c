/*
 *  Advanced Programming Course Assignment 2
 *  Prime Counter program
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

#include "../include/prime_counter.h"
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

PQueue queue;

/*
 * @brief Prime counter main function
 * @param argc number of arguments
 * @param argv array of arguments
 * @return 0 on success, 1 on failure
 */
int main(int argc, char *argv[]) {
	int num;
	int total_counter = 0;
	int proc_count = 0;

	switch (argc)
	{
		// Get the number of processors in the system
		// 0.5 is used to avoid using all the processors and is optimal for this program.
		case 1:
		{
			proc_count = nprocs() * 0.5;
			break;
		}

		case 2:
		{
			proc_count = atoi(argv[1]);

			if (proc_count <= 0)
			{
				fprintf(stderr, "Invalid number of processors.\n");
				return 1;
			}

			break;
		}

		default:
		{
			fprintf(stderr, "Too many arguments.\n");
			return 1;
		}
	}

	pthread_t threads[proc_count];
	int thread_data[proc_count];

	queue = queueCreate();

	// Check if the queue was created successfully
	if (queue == NULL)
	{
		fprintf(stderr, "Error creating queue.\n");
		exit(1);
	}

	// Create threads
	for (int i = 0; i < proc_count; i++)
	{
		thread_data[i] = 0;
		int ret = pthread_create(&threads[i], NULL, &threadTask, &thread_data[i]);

		// Check if the thread was created successfully
		if (ret != 0)
		{
			fprintf(stderr, "Error creating thread.\n");
			return 1;
		}
	}

	// Read numbers from stdin until end of file
	while (scanf("%d", &num) != EOF)
		ENQUEUE(queue, num);

	// Add a sentinel for each thread, so they know when to stop.
	for (int i = 0; i < proc_count; i++)
		ENQUEUE(queue, -1);

	// Wait for all threads to finish and sum their results.
	for (int i = 0; i < proc_count; i++)
	{
		pthread_join(threads[i], NULL);
		total_counter += thread_data[i];
	}

	// Destroy the queue and print the total number of primes.
	queueDestroy(queue);
	fprintf(stdout, "%d total primes.\n", total_counter);

	return 0;
}

int nprocs() {
	cpu_set_t cs;
	CPU_ZERO(&cs);
	sched_getaffinity(0, sizeof(cs), &cs);
	return CPU_COUNT(&cs);
}


// Original isPrime without improvements.
int isPrime(int n) {
	if (n <= 1)
		return 0;
	
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return 0;
	}

	return 1;
}

void *threadTask(void *arg) {
	int *thread_data = (int *)arg;

	while (1)
	{
		int task = DEQUEUE(queue);

		// Safe fail - should never happen.
		if (task < 0)
			break;

		*thread_data += isPrime(task);
	}

	return NULL;
}