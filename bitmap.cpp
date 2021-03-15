#include "bitmap.hpp"

std::ostream& operator<<(std::ostream& output, const Bitmap& map) {
  for (Bitmap::size_type i = 0; i != map.size(); i++) {
    output << map[i];
  }

  return output;
}