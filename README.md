# Advanced Programming Course Assignment 2
### For Computer Science B.S.c Ariel University
**By Roy Simanovich and Almog Shor**

## Description
In this assignment we were asked to create a program that generates a large amount of numbers and then counts the number of prime numbers in the generated list. The program should be able to run in two different configurations: with and without threads. Our main goal was to compare the time it takes to run the program in both configurations and to see if there is a significant difference between them, and to optimize the thread configuration to be as fast as possible, while maintaining low memory usage (2MB limit on the heap).

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
./generator <seed> <num_of_numbers>

# Running the prime counter program with the generator.
./generator <seed> <num_of_numbers> | ./prime_counter_no_thread

# Running the prime counter program in thread mod with the generator.
./generator <seed> <num_of_numbers> | ./prime_counter <num_of_threads>
```

## Example
```
$ time ./generator 0 10000000 | ./prime_counter 8
510755 total primes.

real    0m5.115s
user    0m38.036s
sys     0m4.867s
```

## Notes
* Use `time` command to measure the time it takes to run the program in different configurations (with/without threads).
* Use `valgrind` to check for memory leaks and to see the memory usage (`valgrind --tool=massif ./prime_counter <num_of_threads>`).


## License
This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details.