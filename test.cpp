#include "bitmap.hpp"
#include <iostream>

using namespace std;

#define N 5

int main() {
  Bitmap map(N);

  cout << "Ok" << endl;

  auto ref = map[2];
  ref = true;

  cout << map << endl;

  ref = false;

  cout << map << endl;


  // for (auto bit : map.data) {
  //   cout << bit << endl;
  // }
  // for (int i = 0; i <= N; i++) {
  //   cout << map[i] << endl;
  // }


  return 0;
}