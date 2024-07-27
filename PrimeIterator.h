#ifndef OXIDATION_PRIMEITERATOR_H
#define OXIDATION_PRIMEITERATOR_H

#include <cstddef>
#include <iterator>

struct PrimeIter;

class PrimeIterator {
public:
    class Iterator {
        friend class PrimeIterator;

        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = size_t;

    public:
        Iterator();
        explicit Iterator(PrimeIterator * parent);
        Iterator(const Iterator &) = delete;
        Iterator & operator=(const Iterator &) = delete;
        Iterator(Iterator &&) = delete;
        Iterator & operator=(Iterator &&) = delete;
        ~Iterator() = default;

        value_type operator*() const;
        Iterator & operator++();
        void operator++(int);
        bool operator==(const Iterator &) const;

    private:


        value_type value;
        PrimeIterator* parent;
    };

    friend class PrimeIterator::Iterator;

    PrimeIterator() = delete;
    PrimeIterator(const PrimeIterator &) = delete;
    PrimeIterator & operator=(const PrimeIterator &) = delete;

    explicit PrimeIterator(size_t limit);
    PrimeIterator(PrimeIterator &&) noexcept;
    PrimeIterator & operator=(PrimeIterator &&) noexcept;
    ~PrimeIterator();

    Iterator begin();
    static Iterator end();

    [[nodiscard]] size_t get_limit() const;

private:
    size_t advance_iterator();

    PrimeIter * internal_iterator;
};


#endif //OXIDATION_PRIMEITERATOR_H
