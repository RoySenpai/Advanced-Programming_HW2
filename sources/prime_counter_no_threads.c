/*
 *  Advanced Programming Course Assignment 2
 *  Prime Counter program without threads (made by Arkady).
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
#include <stdio.h>
#include <stdbool.h>

// Function to check if a number is prime
bool isPrime(int n) {
	if (n <= 1)
		return false;
	
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return false;
	}

	return true;
}

int main() {
	int num;
	int total_counter = 0;

	// Read numbers from stdin until end of file
	while (scanf("%d", &num) != EOF)
	{
		if (isPrime(num))
		{
			total_counter++;
		}
	}

	printf("%d total primes.\n", total_counter);

	return 0;
}