#ifndef __BITMAP__
#define __BITMAP__

#include <vector>
#include <stdlib.h>
#include <iostream>

class BitRef {
public:
  // Musn't exist without a referenced value
  BitRef() = delete;

  // Initialization using bit iterator
  BitRef(std::_Bit_iterator initial) : value(*initial) {}

  // Copy constructor
  BitRef(const BitRef& copy) : value(copy.value) {}

  // Assignment
  bool operator=(const bool new_value) { return value = new_value; }

  // Destructor
  ~BitRef() = default;

  // Conversion to bool
  operator bool() const { return value; }

private:
  std::_Bit_iterator::reference value;
};

class Bitmap {
public:
  typedef std::vector<bool>::size_type size_type;

  // Constructs a new bitmap that can store n bits
  explicit Bitmap(const size_type n) : bitmap(n) {};

  // Constructs a copy of b1, and trims it to the size of n bits
  // Any additional bits are set to 0 (false)
  Bitmap(const size_type n, const Bitmap& b1) : bitmap(b1.bitmap) { bitmap.resize(n); }

  // ELEMENT ACCESS

  // Returns a bool corresponding to the nth element of the bitmap
  bool operator[](size_type index) const { return bitmap[index]; }

  // Returns a reference to the nth element
  BitRef operator[](size_type index) { return BitRef(bitmap.begin() + index); }

  // Access element with bound checking
  BitRef at(size_type index);
  bool at(size_type index) const;

  // MODIFIERS

  // Inverts all bits
  Bitmap operator!() const;

  // Returns element-wise OR
  Bitmap operator+(Bitmap map) const { return operate(*this, map, [](bool a, bool b) { return a || b; }); }

  // Returns element-wise AND
  Bitmap operator*(Bitmap map) const { return operate(*this, map, [](bool a, bool b) { return a && b; }); }

  // Returns element-wise XOR
  Bitmap operator^(Bitmap map) const {
    return operate(*this, map, [](bool a, bool b) { return (a + b) == 1; });
  }

  // Returns element-wise relative complement
  Bitmap operator-(Bitmap map) const {
    return operate(*this, map, [](bool a, bool b) { return (a - b) == 1; });
  }

  // Returns the bitmap repeated n times
  Bitmap operator*(int n) const;

  // CAPACITY

  // Returns the bitmap length
  size_type size() const { return bitmap.size(); }

private:
  // Applies provided operation for each pair of elements from both maps and returns resulting map
  Bitmap operate(const Bitmap& map1, const Bitmap& map2, bool operation(bool, bool)) const;

  std::vector<bool> bitmap;
};

std::ostream& operator<<(std::ostream&, const Bitmap&);

Bitmap operator*(const int n, const Bitmap map);

#endif