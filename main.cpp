#include <iostream>

#include "PrimeIterator.h"

int main() {
    size_t limit = 500;
    auto primes = PrimeIterator(limit);
    if (limit == primes.get_limit()) {
        std::cout << "Found correct limit" << std::endl;
    } else {
        std::cout << "Failed to find correct limit" << std::endl;
    }

    for (auto prime : primes) {
        std::cout << "Found prime number " << prime << "\n";
    }

    return 0;
}
