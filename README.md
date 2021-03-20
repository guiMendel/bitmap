
# Bitmap class
Provides a bitmap c++ class implementation.
A bitmap is essentially an array of bits.

## Usage and compilation
To use the class, just add `#include "path/to/bitmap.hpp"` to your own header file.

When compiling, make sure to use at least `c++17` and include bitmap.cpp on your command. It should look something like this:
```
g++ -std=c++17 <your-files> bitmap.cpp -o <output-file>
``` 

## Interface
Assume `n` is a positive integer and `b` is a BitMap of the same size as the the subject Bitmap.
### Member functions
- `Bitmap(n)` constructs a new bitmap that can store 𝑛 bits. All bits are initially set to 0.
- `Bitmap(n, b)` constructs a copy of b1. If 𝑛 is smaller than the size of b1, the bitmap is truncated to the first 𝑛 bits of b1. If 𝑛 is greater than the size of b1, additional bits are set to 0.
- 0-based indexing with the `[]` operator:
	- `bool operation[](n) const` returns a bool, which is true if the 𝑛th bit of b1 is 1 and false otherwise.
	- `BitRef operation[](n)` returns a special proxy class `BitRef`, as C++ does not allow references to bool. This class is described below.
	- The `[]` operation does not do any bounds checking, the result is unspecified (and can be a crash) if 𝑛 is greater or equal to the size of b1.
- `at(n)` returns `(*this)[n]`, but additionally does bounds checking, and **throws exception** `std::out_of_range` if 𝑛 is greater or equal to the size of the bitmap.
- `size()` returns the number of bits in the array.
- `operator!()` returns a new bitmap that is the negation of b1, i.e. the 𝑛th bit of the result is 1 iff the 𝑛th bit of b1 is 0.
- `operator+(b)` returns a new bitmap that is the union of b1 and b2, i.e. the 𝑛th bit of the result is 1 iff the 𝑛th bit is set (i.e. equals 1) in b1, b2, or both.
- `operator*(b)` returns a new bitmap that is the intersection of b1 and b2, i.e. the 𝑛th bit of the result is 1 iff the 𝑛th bit is set in both b1 and b2.
- `operator-(b)` returns a new bitmap that is the set difference (or relative complement) of b1 and b2, i.e. the 𝑛th bit of the result is 1 iff the 𝑛th bit is set in b1 but not in b2.
- `operator^(b)` returns a new bitmap that is the symmetric difference (or disjunctive union) of b1 and b2, i.e. the 𝑛th bit of the result is 1 iff the 𝑛th bit of b1 or b2 is set, but not both. 
- `operator*(n)` returns a bitmap that repeats the sequence of bits 𝑛 times, e.g. if it contains 100110, then `b * 3` should return a bitmap that contains 100110 100110 100110. See also non-member function `operator*(n, b)`, which provides comutativity to this operation.

### Non-member functions
- `operator<<(ostream, b)` prints b as a text sequence of 0s and 1s on the output stream, where `b[0]` appears as the *rightmost* bit.
- `operator*(n, b)` returns a bitmap that repeats 𝑛 times the sequence of bits in b. See also member function `operator*(n)`.
