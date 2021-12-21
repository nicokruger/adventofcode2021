#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;

class Rolling3 {
  float vals[3];
  int num;
  public:
    Rolling3() : num(0) { }
    Rolling3 &operator << (float v) {
      vals[++num % 3] = v;
      return *this;
    }
    float sum() const {
      if (!filled()) {
        throw -1; 
      }
      return vals[0] + vals[1] + vals[2];
    }
    bool filled() const {
      return num >= 3;
    }

    operator float() const {
      return this->sum();
    }

    const Rolling3 &operator = (const Rolling3 &b) {
      this->vals[0] = b.vals[0];
      this->vals[1] = b.vals[1];
      this->vals[2] = b.vals[2];
      this->num = b.num;
      return *this;
    }
};

void run() {
  cout << "hi" << endl;
  ifstream f("data.txt");

  std::string line;
  float num;
  Rolling3 w1, w2;
  Rolling3 &active = w1;
  int count = 0;
  int lines = 0;
  while (getline(f, line)) {
    num = std::stof(line);

    w1 << num;

    if (!w1.filled()) {
      continue;
    }

    if (!w2.filled()) {
      w2 = w1;
      continue;
    }
    if (w1 > w2) {
      count++;
    }
    w2 = w1;
  }
  cout << "total: " << count << endl;
}

void test() {
  Rolling3 r3;
  r3 << 500;
  assert( r3.filled() == false );
  r3 << 100;
  assert( r3.filled() == false );
  r3 << 200;
  assert( r3.filled() == true );
  assert( r3.sum() == 800 );

  Rolling3 cp;
  cp = r3;
  assert( cp.filled() == true );
  assert( cp.sum() == 800 );
}

int main() {
  test();
  run();
}
