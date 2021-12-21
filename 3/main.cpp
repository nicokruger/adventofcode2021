#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;


void run() {
  ifstream f("input.txt");

  std::string line;
  float num;
  Rolling3 w1, w2;
  Rolling3 &active = w1;
  int count = 0;
  int lines = 0;
  while (getline(f, line)) {
  }
}

void test() {
}

int main() {
  test();
  run();
}
