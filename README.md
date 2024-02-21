# Advanced Programming Course Assignment 2
### For Computer Science B.S.c Ariel University
**By Roy Simanovich and Almog Shor**

## Description
In this assignment we were asked to create a program that generates a large amount of numbers and then counts the number of prime numbers in the generated list.
The program should be able to run in two different configurations: with and without threads. Our main goal was to compare the time it takes to run the program
in both configurations and to see if there is a significant difference between them, and to optimize the thread configuration to be as fast as possible,
while maintaining low memory usage (2MB limit on the heap).


### The generator program
The generator program is responsible for generating a large amount of numbers and printing them to the standard output. The program should be able to
generate a large amount of numbers (up to 10^7) and should be able to generate the same list of numbers with the same seed. The program should be able
to run in a reasonable amount of time (up to 10 seconds for 10^7 numbers).

### Results
On our machine that we tested the program on, we were able to improve the time it takes to run the program by 7x when using 16 threads instead of a
single thread, without improving the isPrime function. When we improved the isPrime function, we were able to improve the time it takes to run the
program by 14x when using 3 threads instead of a single thread. Memory usage stayed low, about 40KB heap usage for both improved and not improved
isPrime functions.

Below are the results of the program running with different configurations (notice that for the 10^9 numbers test, we only ran the program
with 3 threads, as the program with 16 threads took too long to run, and the same goes for the single thread program):
```
$ time ./randomGenerator 0 10000000 | ./prime_counter_no_threads
491346 total primes.

real    0m41.147s
user    0m41.644s
sys     0m0.399s

$ time ./randomGenerator 0 10000000 | ./prime_counter_only_threads 16
491346 total primes.

real    0m6.326s
user    1m30.460s
sys     0m3.921s

$ time ./randomGenerator 0 10000000 | ./primesCounter 3
491346 total primes.

real    0m2.997s
user    0m9.219s
sys     0m2.389s

$ time ./randomGenerator 0 100000000 | ./prime_counter_no_threads
4921867 total primes.

real    6m54.246s
user    6m58.884s
sys     0m4.378s

$ time ./randomGenerator 0 100000000 | ./prime_counter_only_threads 16
4921867 total primes.

real    1m5.550s
user    15m46.432s
sys     0m35.806s

$ time ./randomGenerator 0 100000000 | ./primesCounter 3
4921867 total primes.

real    0m29.572s
user    1m29.642s
sys     0m24.544s

$ time ./randomGenerator 0 1000000000 | ./primesCounter 3
49219283 total primes.

real    5m2.676s
user    15m4.609s
sys     4m13.652s
```

## Requirements
* Linux machine (Ubuntu 22.04 LTS preferable)
* GNU C Compiler
* Make

## Building
```
# Cloning the repo to local machine.
git clone https://github.com/RoySenpai/Advanced-Programming_HW2.git

# Building all the necessary files & the main programs.
make all
```

## Running
```
# Running the generator program.
./randomGenerator <seed> <num_of_numbers>

# Running the prime counter program with the generator.
./randomGenerator <seed> <num_of_numbers> | ./prime_counter_no_thread

# Running the prime counter program in thread mod (isPrime improved) with the generator.
./randomGenerator <seed> <num_of_numbers> | ./primesCounter <num_of_threads>

# Running the prime counter program in thread mod (isPrime not improved) with the generator.
./randomGenerator <seed> <num_of_numbers> | ./prime_counter_only_threads <num_of_threads>
```

## Example
```
$ time ./randomGenerator 0 10000000 | ./primesCounter 8
510755 total primes.

real    0m5.115s
user    0m38.036s
sys     0m4.867s
```

## Notes
* Use `time` command to measure the time it takes to run the program in different configurations (with/without threads).
* Use `valgrind` to check for memory leaks and to see the memory usage (`valgrind --tool=massif ./primesCounter <num_of_threads>`).


## License
This project is licensed under the GNU GPLv3 License - see the [LICENSE](LICENSE) file for details.