#include "bitmap.hpp"
#include <iostream>
#include <cassert>

using namespace std;

#define N 5

int main() {
  Bitmap map(N);

  cout << "Ok" << endl;

  map[2] = true;
  map[4] = true;

  cout << "Original: " << map << endl;

  Bitmap map2(3, map);

  cout << "Trim copy: " << map2 << endl;

  cout << "Bang: " << !map << endl;

  Bitmap map3(N);
  map3[0] = true;
  map3[2] = true;

  cout << "Sum: " << map3 + map << endl;

  cout << "Mult: " << map3 * map << endl;

  cout << "Sub: " << map3 - map << endl;

  cout << "Xor: " << (map3 ^ map) << endl;

  cout << "Ok\nExpected: " << map << map << map << endl;

  cout << "Repeat:   " << (3 * map) << endl;

  auto bit = map[0];
  bit = true;
  map.at(0) = false;
  cout << "Final: " << map << endl;
  cout << "Bit: " << bit << endl;

  // for (auto bit : map.data) {
  //   cout << bit << endl;
  // }
  // for (int i = 0; i <= N; i++) {
  //   cout << map[i] << endl;
  // }

  return 0;
}