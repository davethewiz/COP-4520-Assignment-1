#include <iostream>
using namespace std;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

#include <thread>
#include <mutex>
#include <vector>

#include<math.h>

const int THREAD_COUNT = 8;

const int NUM_COUNT = 1e8;
bool is_prime[NUM_COUNT+1];


// simple prime checker (not used for sieve)
bool check_prime(int num) {
    if (num == 0 || num == 1)
        return false;

    for (int i = 2; i*i < num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

void sieve() {
    for (long i = 0; i <= sqrt(NUM_COUNT); i++) {
        if (!is_prime[i]) {
            continue;
        }
    
        for (long j = i*i; j <= NUM_COUNT; j += i) {
            is_prime[j] = false;
        }
    }
}

void calc_prime_range(int low, int high) {
    for (int num = low; num <= high; num++) {
        is_prime[num] == check_prime(num);
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

    cout << "sum: " << sum << " -  count: " << prime_count << "\n";

    for (int &top : top_ten)
        cout << top << " ";

    cout << "\n";

    cout << runtime_ms << " ms\n";
}

int main() {
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i <= NUM_COUNT; i++) {
        is_prime[i] = true; // assume (initially) that all numbers are prime
    }

    is_prime[0] = false;
    is_prime[1] = false;

    sieve();

    auto end_time = high_resolution_clock::now();
    int duration = duration_cast<milliseconds>(end_time - start_time).count();

    print_result(duration);

    return 0;
}