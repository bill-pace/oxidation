#ifndef OXIDATION_PRIME_ITER_H
#define OXIDATION_PRIME_ITER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct PrimeIter;

struct PrimeIter * alloc_prime_iter(uintptr_t limit);

void free_prime_iter(struct PrimeIter * iter);

uintptr_t advance_iter(struct PrimeIter * iter);

uintptr_t get_iter_limit(struct PrimeIter const * iter);

#ifdef __cplusplus
}; // end 'extern "C"'
#endif

#endif //OXIDATION_PRIME_ITER_H
