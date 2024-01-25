#include <iostream>
#include<fstream>
using namespace std;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

#include <thread>
#include <vector>

const int THREAD_COUNT = 8;

const int NUM_COUNT = 1e8;
bool is_prime[NUM_COUNT+1];


// simple prime checker (not used for sieve)
bool check_prime(int num) {
    if (num == 0 || num == 1) return false;

    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

// sets a range of prime values
void calc_prime_range(int low, int high) {
    for (int num = low; num <= high; num++) {
        is_prime[num] = check_prime(num);
    }
}

void print_result(int runtime_ms) {
    long long sum = 0;
    int prime_count = 0;

    vector<int> top_ten;

    for (int i = NUM_COUNT; i >= 0; i--) {
        if (is_prime[i]) {
            prime_count++;
            sum += i;

            if (top_ten.size() < 10)
                top_ten.insert(top_ten.begin(), i);
        }
    }

    ofstream output_file;
    output_file.open("primes.txt");

    output_file << runtime_ms << "ms ";
    output_file << sum << " " << prime_count << "\n";

    for (int &top : top_ten)
        output_file << top << " ";
}

int main() {
    auto start_time = high_resolution_clock::now();

    vector<thread> threads;
    int nums_per_thread = NUM_COUNT / THREAD_COUNT;

    // spawn all threads
    for (int t = 0; t < THREAD_COUNT; t++)
        threads.push_back(thread(calc_prime_range, nums_per_thread * t, nums_per_thread * (t+1)));

    // join all threads after execution
    for (thread &t : threads)
        t.join();
    
    // calculate execution time
    auto end_time = high_resolution_clock::now();
    int runtime_ms = duration_cast<milliseconds>(end_time - start_time).count();
    
    print_result(runtime_ms);

    return 0;
}