mod primes;

pub struct PrimeIter;

#[no_mangle]
pub extern "C" fn alloc_prime_iter(limit: usize) -> *mut PrimeIter {
    let iter = Box::new(match primes::Primes::new(limit) {
        Ok(primes) => primes,
        Err(_) => return 0 as *mut PrimeIter, // just swallow the error and hand back a nullptr
    });
    let ptr = Box::leak(iter); // relinquish ownership to caller
    ptr as *mut primes::Primes as *mut PrimeIter // make pointer opaque
}

#[no_mangle]
pub extern "C" fn free_prime_iter(ptr: *mut PrimeIter) {
    if ptr == 0 as *mut PrimeIter {
        // freeing a nullptr should always be a no-op so don't waste time
        // standing up a Box to claim ownership of nothing
        return;
    }

    let ptr = ptr as *mut primes::Primes;
    unsafe {
        // safety: must assume that the caller uniquely owns the referent
        // iterator and that the pointer is valid. correct management is the
        // client's responsibility here, as was determined by relinquishing
        // ownership in the matching alloc_prime_iter function above
        // impl: hand the pointer to a box and let Box::drop do its thing
        let _ = Box::from_raw(ptr);
    }
}

#[no_mangle]
pub extern "C" fn advance_iter(ptr: *mut PrimeIter) -> usize {
    let iter = unsafe {
        // safety: must assume caller has exclusive access to the iterator
        // when calling this function. will panic if passed a nullptr
        (ptr as *mut primes::Primes).as_mut().unwrap()
    };
    iter.next().unwrap_or_else(|| 0)
}

#[no_mangle]
pub extern "C" fn get_iter_limit(ptr: *const PrimeIter) -> usize {
    let iter = unsafe {
        // safety: must assume caller has valid shared access
        // to the iterator at the time of calling this function
        // will panic if passed a nullptr
        (ptr as *const primes::Primes).as_ref().unwrap()
    };
    iter.limit()
}
