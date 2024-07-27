#[derive(Copy, Clone, Debug, Eq, PartialEq)]
pub enum Error {
    LimitTooHigh,
    LimitTooLow,
}

pub struct Primes {
    current: usize,
    limit: usize,
    cache: Vec<bool>,
}

impl Primes {
    pub fn new(limit: usize) -> Result<Self, Error> {
        if limit < 2 {
            return Err(Error::LimitTooLow);
        }
        if limit >= usize::MAX / 2 {
            return Err(Error::LimitTooHigh);
        }

        let mut cache = vec![true; limit + 1];
        cache[0] = false;
        cache[1] = false;
        Ok(Self {
            current: 1,
            limit,
            cache,
        })
    }

    pub fn limit(&self) -> usize {
        self.limit
    }
}

impl Iterator for Primes {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        while self.current < self.limit {
            self.current += 1;
            if self.cache[self.current] {
                // found a prime number, mark its multiples as composite and return it
                let mut multiple = self.current * 2;
                while multiple <= self.limit {
                    self.cache[multiple] = false;
                    multiple += self.current;
                }
                return Some(self.current);
            }
        }
        None
    }
}

#[cfg(test)]
mod test {
    #[test]
    fn iter_gets_correct_primes() {
        let expected = vec![2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47];
        let iter = super::Primes::new(50).unwrap();
        let actual: Vec<_> = iter.collect();
        assert_eq!(expected, actual);
    }
}
