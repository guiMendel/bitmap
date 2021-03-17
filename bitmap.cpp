#include "bitmap.hpp"
#include <cstring>

std::ostream& operator<<(std::ostream& output, const Bitmap& map) {
  for (Bitmap::size_type i = 0; i < map.size(); i++) {
    output << map[i];
  }

  return output;
}

BitRef Bitmap::at(const size_type index) {
  if (index >= size()) throw std::out_of_range("Target index is out of range");
  return (*this)[index];
}

bool Bitmap::at(const size_type index) const {
  if (index >= size()) throw std::out_of_range("Target index is out of range");
  return (*this)[index];
}

Bitmap Bitmap::operator!() const {
  auto copy = Bitmap(*this);

  // vector<bool> already comes with a method that does the heavy lifting for us
  copy.bitmap.flip();

  return copy;
}

Bitmap Bitmap::operate(const Bitmap& map1, const Bitmap& map2, bool operation(bool, bool)) const {
  // Gets arrays size
  auto length = map1.size();

  // Makes sure they're both equally big
  if (map2.size() != length) throw std::domain_error("Both bitmaps must have the same size");

  // Prepares new empty bitmap
  Bitmap result(length);

  // Applies operation on each pair and fills up the resulting array
  for (Bitmap::size_type i = 0; i != length; i++) {
    result[i] = operation(map1[i], map2[i]);
  }

  return result;
}

Bitmap Bitmap::operator*(int n) const {
  // Creates resulting bitmap
  Bitmap result(0);

  // Gets the bitmap size in bytes
  size_type map_size = size() * sizeof(bool);

  // Pastes the bitmap in n times
  for (size_type i = 0; i < n; i++) {
    result.bitmap.insert(
      result.bitmap.begin() + map_size * i,
      bitmap.begin(),
      bitmap.end()
    );
  }

  return result;
}

// As simple as this is, defining it in the header file messes the compilation up
Bitmap operator*(const int n, const Bitmap map) { return map * n; }
