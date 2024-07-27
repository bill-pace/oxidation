#include <iostream>

#include "prime_iter.h"

int main() {
    size_t limit = 50;
    PrimeIter * iterator = alloc_prime_iter(limit);
    size_t read_limit = get_iter_limit(iterator);
    if (read_limit == limit) {
        std::cout << "Successfully re-read the limit" << std::endl;
    } else {
        std::cout << "Oops" << std::endl;
    }

    while (size_t prime = advance_iter(iterator)) {
        std::cout << "Found prime " << prime << std::endl;
    }

    free_prime_iter(iterator);

    return 0;
}
