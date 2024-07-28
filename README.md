This sample project demonstrates how to link a Rust library from C++ code through a C header.

The Rust library here defines an iterator that yields prime numbers when calling next(). The
iterator is publicly exposed via an opaque struct and four free functions that enable
alloc/free, advancing the iterator, and checking its upper limit.

The C++ class PrimeIterator wraps these exposed functions to provide RAII and an input iterator, showcased in the main() function. Proper cleanup can be confirmed by running Valgrind or similar tools.

Note that building this project offline will require changes to the CMake file in order to
have offline access to the Corrosion package. However, the Rust library has no dependencies
and therefore you will not need to pull anything from crates.io ahead of time.
