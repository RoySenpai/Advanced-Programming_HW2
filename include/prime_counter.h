/*
 *  Advanced Programming Course Assignment 2
 *  Prime Counter header file
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

#ifndef _PRIME_COUNTER_H
#define _PRIME_COUNTER_H


/*******************/
/* Defines Section */
/*******************/

/*
 * @brief Allow the GNU extensions of POSIX functions to be used.
 */
#if !defined(_XOPEN_SOURCE) && !defined(_POSIX_C_SOURCE)
	#if __STDC_VERSION__ >= 199901L
		#define _XOPEN_SOURCE 600 /* SUS v3, POSIX 1003.1 2004 (POSIX 2001 + Corrigenda) */
	#else
		#define _XOPEN_SOURCE 500 /* SUS v2, POSIX 1003.1 1997 */
	#endif					  /* __STDC_VERSION__ */
#endif					  /* !_XOPEN_SOURCE && !_POSIX_C_SOURCE */

/*
 * @brief Required for CPU_SET and CPU_ZERO
*/
#define _GNU_SOURCE


/********************/
/* Includes Section */
/********************/
#include "Queue.h"
//#include <stdbool.h>


/*********************/
/* Functions Section */
/*********************/

/*
 * @brief Function that checks the number of processors in the system.
 * @return The number of processors in the system.
*/
int nprocs();

/*
 * @brief Function that checks if a number is prime.
 * @param n The number to be checked if it is prime.
 * @return True if the number is prime, false otherwise.
*/
int isPrime(int n);

/*
 * @brief Function that is executed by each thread.
 * @param arg The number of primes found by the thread.
 * @return NULL.
*/
void *threadTask(void *arg);


#endif