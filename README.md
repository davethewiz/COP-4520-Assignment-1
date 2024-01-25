# COP 4520 - Assignment 1
This repository contains the code for the first assignment in COP 4520 Spring 2024.

This code finds all prime numbers between $1$ and $10^8$ and prints out the results in file called `primes.txt`.
It does this by implementing a multi-threaded / concurrent approach to a simple prime checking algorithm.

### Compiling and Running
To run this program, clone this repository and open the terminal from within the main project directory.
Once the terminal is open type in the following command to create an compile and create an executable called "calculate primes":
```
g++ main.cpp -o "calculate primes"
```

Run the executable by running the following command:
```
& '.\calculate primes'
```

### Output
The final output of this code will be printed to a file called `primes.txt`.
The format of this output is organized as follows:
```
<execution time> <total number of primes found> <sum of all primes found>
<top ten maximum primes, listed in order from lowest to highest>
```

Note that execution time is shown in `ms` or milliseconds.

### Design and Evaluation
The design of the code is quite simple, there is a large array that represents the list of all numbers and whether they are prime.

The code first spawns 8 threads that are each given 1/8th of the total numbers to calculate. This allows the threads to each receive just about an equal number of calculations.
Since each thread deals with a different set of numbers, there is no race conditions or shared recourses.

Each thread iterates through its set of numbers and determines whether a number $n$ is prime by taking the modulus of all numbers from $2$ to $\sqrt n$. If none of those modulus operations returns $0$ then $n$ is prime, otherwise, composite.

Once all threads have completed, all prime numbers from $1$ to $10^8$ have been found and the final results are printed in the output format described above.

As a result of the algorithm chosen, this code is able to produce an output in just over 10 seconds when using all 8 threads. Thanks to an even set of calculations among all threads, this program is able to efficiently calculate many prime numbers relatively quickly.
