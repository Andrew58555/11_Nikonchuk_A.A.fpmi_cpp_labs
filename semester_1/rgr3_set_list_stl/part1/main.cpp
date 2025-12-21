#include <iostream>
#include <set>
#include <cmath>

std::set<int> findPrimesUsingSet(int n) {
    std::set<int> primes;

    for (int i = 2; i <= n; ++i) {
        primes.insert(i);
    }

    for (int p = 2; p * p <= n; ++p) {
        if (primes.find(p) != primes.end()) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                primes.erase(multiple);
            }
        }
    }

    return primes;
}

void printPrimes(const std::set<int>& primes) {
    std::cout << "Prime numbers: ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;

    std::cout << "Enter number n: ";
    if (!(std::cin >> n)) {
        std::cout << "Wrong input" << std::endl;
        return 1;
    }

    if (n < 2) {
        std::cout << "No prime numbers less than or equal to " << n << std::endl;
        return 0;
    }

    std::set<int> primes = findPrimesUsingSet(n);

    std::cout << "Prime numbers not exceeding " << n << ":" << std::endl;
    printPrimes(primes);
    std::cout << "Number of prime numbers: " << primes.size() << std::endl;

    return 0;
}
