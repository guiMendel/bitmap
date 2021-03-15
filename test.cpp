#include "bitmap.hpp"
#include <iostream>

using namespace std;

#define N 5

int main() {
  Bitmap map(N);

  cout << "Ok" << endl;

  // map.data[2] = true;

  // for (auto bit : map.data) {
  //   cout << bit << endl;
  // }
  // for (int i = 0; i <= N; i++) {
  //   cout << map[i] << endl;
  // }

  cout << map << endl;

  bool meme = true;
  BitRef ref(&meme);
  ref = false;

  cout << meme << endl;

  return 0;
}