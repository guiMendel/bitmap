#ifndef __BITMAP__
#define __BITMAP__

#include <vector>
#include <stdlib.h>
#include <iostream>

/// A reference to an element from a Bitmap
class BitRef {
public:
  // Musn't exist without a referenced value
  BitRef() = delete;

  /**
   * Initialization using bit iterator
   *
   * Dereferences the iterator and stores its content, which is a reference
   *
   * @param initial An iterator pointing to an element from a Bitmap
   */
  BitRef(std::_Bit_iterator initial) : value(*initial) {}

  /**
   * Copy constructor
   *
   * @param copy Some other BitRef whose value is to be copied to this BitRef
   */
  BitRef(const BitRef& copy) : value(copy.value) {}

  /**
   * Assignment operator
   *
   * Overrides the referenced element's value, effectively modifying it's parent Bitmap
   *
   * @param new_value The new value
   * @returns new_value
   */
  bool operator=(const bool new_value) { return value = new_value; }

  /// Default destructor
  ~BitRef() = default;

  /**
   * Conversion to bool
   *
   * @returns The referenced value casted as a bool
   */
  operator bool() const { return (bool)value; }

private:
  /// The stored reference to a Bitmap's element
  std::_Bit_iterator::reference value;
};

/**
 * A fixed-length array of bits
 *
 * Stores bits as bools in a vector
 */
class Bitmap {
public:
  /// Defines the size_type for the bits
  typedef std::vector<bool>::size_type size_type;

  friend std::ostream& operator<<(std::ostream& output, const Bitmap& map);

  /**
   * Constructs a new bitmap with the provided length
   *
   * @param n The length of the bitmap
   */
  explicit Bitmap(const size_type n) : bitmap(n) {};

  /**
   * Constructs a copy of b1, and resizes it to the provided length
   *
   * If new length is bigger, additional bits are set to 0 (false).
   * If smaller, trims tailing bits.
   *
   * @param n The length of the bitmap
   * @param b1 The Bitmap to be copied
   */
  Bitmap(const size_type n, const Bitmap& b1) : bitmap(b1.bitmap) { bitmap.resize(n); }

  // ELEMENT ACCESS

  /**
   * Copies the selected element as a bool
   *
   * Does not perform bound checking. Out of bounds selection results in undetermined behaviour
   *
   * @param index The index of the element to be accessed
   * @returns A bool corresponding to the selected element
   */
  bool operator[](size_type index) const { return bitmap[index]; }

  /**
   * Returns a reference to the selected element
   *
   * Does not perform bound checking. Out of bounds selection results in undetermined behaviour
   *
   * @param index The index of the element to be accessed
   * @returns A BitRef to the selected element
   * @see BitRef
   */
  BitRef operator[](size_type index) { return BitRef(bitmap.begin() + index); }

  /**
   * Returns a reference to the selected element
   *
   * Performs bound checking
   *
   * @param index The index of the element to be accessed
   * @returns A BitRef to the selected element
   * @see BitRef
   * @throws std::out_of_range if the provided index surpasses the bitmap's size
   * @exceptsafe strong
   */
  BitRef at(size_type index);

  /**
   * Copies the selected element as a bool
   *
   * Performs bound checking
   *
   * @param index The index of the element to be accessed
   * @returns A bool corresponding to the selected element
   * @see BitRef
   * @throws std::out_of_range if the provided index surpasses the bitmap's size
   * @exceptsafe strong
   */
  bool at(size_type index) const;

  // MODIFIERS

  /**
   * Inverts all bits
   *
   * All 1s become 0s and all 0s become 1s
   * @returns The resulting Bitmap
   */
  Bitmap operator!() const;

  /**
   * Performs element-wise OR
   *
   * @param map The second Bitmap on which to perform the operation
   * @returns The element-wise OR Bitmap
   */
  Bitmap operator+(Bitmap map) const { return operate(*this, map, [](bool a, bool b) { return a || b; }); }

  /**
   * Performs element-wise AND
   *
   * @param map The second Bitmap on which to perform the operation
   * @returns The element-wise AND Bitmap
   */
  Bitmap operator*(Bitmap map) const { return operate(*this, map, [](bool a, bool b) { return a && b; }); }

  /**
   * Performs element-wise XOR
   *
   * @param map The second Bitmap on which to perform the operation
   * @returns The element-wise XOR Bitmap
   */
  Bitmap operator^(Bitmap map) const {
    return operate(*this, map, [](bool a, bool b) { return (a + b) == 1; });
  }

  /**
   * Performs element-wise relative complement
   *
   * @param map The second Bitmap on which to perform the operation
   * @returns The element-wise relative complement Bitmap
   */
  Bitmap operator-(Bitmap map) const {
    return operate(*this, map, [](bool a, bool b) { return (a - b) == 1; });
  }

  /**
   * Concatenates the bitmap with itself n times
   *
   * @param n The number of copies to be present on the new bitmap
   * @returns The concatenated Bitmap
   */
  Bitmap operator*(int n) const;

  // CAPACITY

  /// Returns the bitmap length
  size_type size() const { return bitmap.size(); }

private:
  /**
   * Applies provided operation for each pair of elements with equal index from both maps
   *
   * Creates a new Bitmap that stores the results on the corresponding index.
   * Both maps must have the same length
   *
   * @param map1 The first Bitmap on which to perform the operation
   * @param map2 The second Bitmap on which to perform the operation
   * @param operation A function that takes two bools and returns another bool
   * @returns A Bitmap of the results
   * @throws std::domain_error if the provided bitmaps don't share the same length
   * @exceptsafe strong
   */
  Bitmap operate(const Bitmap& map1, const Bitmap& map2, bool operation(bool, bool)) const;

  /// A vector of bools, corresponding to the actual bitmap
  std::vector<bool> bitmap;
};

/**
 * Outputs a Bitmap as an array of 0s and 1s
 *
 * @param output A reference to the ostream where to output the array
 * @param map A reference to the Bitmap to be outputted
 * @returns The ostream
 */
std::ostream& operator<<(std::ostream& output, const Bitmap& map);

/**
 * Provides comutativity to operator*(int) method from Bitmap 
 * 
 * @see Bitmap::operator*(int n)
 */
Bitmap operator*(const int n, const Bitmap map);

#endif