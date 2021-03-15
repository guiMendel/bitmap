#ifndef __BITMAP__
#define __BITMAP__

#include <vector>
#include <stdlib.h>
#include <iostream>

class BitRef {
public:
  BitRef() {}

  // Initialization using pointer to bool
  BitRef(std::_Bit_iterator initial) : value(initial) {}

  // Copy constructor
  BitRef(const BitRef& copy) : BitRef(copy.value) {}

  // Assignment
  bool operator=(const bool new_value) { return *value = new_value; }

  // Conversion to bool
  operator bool() const { return *value; }

private:
  std::_Bit_iterator value;
};

class Bitmap {
public:
  typedef std::vector<bool>::size_type size_type;

  // Constructs a new bitmap that can store n bits
  explicit Bitmap(size_type n) : bitmap(n) {};

  // Constructs a copy of b1, and trims it to the size of n bits
  // Any additional bits are set to 0 (false)
  Bitmap(size_type n, const Bitmap& b1) : bitmap(b1.bitmap) { bitmap.resize(n); }

  // Returns a bool corresponding to the nth element of the bitmap
  const bool operator[](size_type index) const { return bitmap[index]; }

  // Returns a reference to the bool
  BitRef operator[](size_type index) { return BitRef(bitmap.begin() + index); }

  // Returns the bitmap length
  size_type size() const { return bitmap.size(); }

// private:
  std::vector<bool> bitmap;
};

std::ostream& operator<<(std::ostream&, const Bitmap&);

#endif