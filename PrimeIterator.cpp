#include "PrimeIterator.h"

#include "prime_iter.h"

#include <iterator>

static_assert(std::input_iterator<PrimeIterator::Iterator>);

PrimeIterator::PrimeIterator(size_t limit) {
    internal_iterator = alloc_prime_iter(limit);
}

PrimeIterator::PrimeIterator(PrimeIterator && other) noexcept {
    internal_iterator = other.internal_iterator;
    other.internal_iterator = nullptr;
}

PrimeIterator & PrimeIterator::operator=(PrimeIterator && other) noexcept {
    if (&other == this) return *this;
    free_prime_iter(internal_iterator);
    internal_iterator = other.internal_iterator;
    other.internal_iterator = nullptr;
    return *this;
}

PrimeIterator::~PrimeIterator() {
    free_prime_iter(internal_iterator);
}

size_t PrimeIterator::get_limit() const {
    return get_iter_limit(internal_iterator);
}

size_t PrimeIterator::advance_iterator() {
    return advance_iter(internal_iterator);
}

PrimeIterator::Iterator PrimeIterator::begin() {
    return PrimeIterator::Iterator(this);
}

PrimeIterator::Iterator PrimeIterator::end() {
    return {};
}

PrimeIterator::Iterator::Iterator() :
    value(0),
    parent(nullptr)
{

}

PrimeIterator::Iterator::Iterator(PrimeIterator * parent) :
    value(0),
    parent(parent)
{
    value = parent->advance_iterator();
}

PrimeIterator::Iterator::Iterator(Iterator && other) noexcept :
    value(other.value),
    parent(other.parent)
{
    other.value = 0;
    other.parent = nullptr;
}

PrimeIterator::Iterator & PrimeIterator::Iterator::operator=(Iterator && other) noexcept {
    if (&other == this) return *this;

    value = other.value;
    parent = other.parent;
    other.value = 0;
    other.parent = nullptr;
    return *this;
}

PrimeIterator::Iterator::value_type PrimeIterator::Iterator::operator*() const {
    return value;
}

PrimeIterator::Iterator & PrimeIterator::Iterator::operator++() {
    value = parent->advance_iterator();
    return *this;
}

void PrimeIterator::Iterator::operator++(int) {
    ++*this;
}

bool PrimeIterator::Iterator::operator==(const PrimeIterator::Iterator & other) const {
    return this->value == other.value &&
        (value == 0 || this->parent == other.parent);
}
