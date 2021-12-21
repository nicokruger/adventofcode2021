#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <assert.h>

using namespace std;

class SubPos {
private:
  int _x;
  int _y;
public:
  SubPos() : _x(0), _y(0) { }
  SubPos(int _x, int _y) : _x(_x), _y(_y) { };
  SubPos(const SubPos &a) : _x(a._x), _y(a._y) { };

  SubPos operator + (const SubPos &b) {
    SubPos p(this->_x + b._x, this->_y + b._y);
    return p;
  }

  int x() { return _x; }
  int y() { return _y; }


};

SubPos parse(const string &line, SubPos currentPos) {

  istringstream iss{line};

  vector<string> words((istream_iterator<string>(iss)),
                       istream_iterator<string>());

  assert(words.size() == 2);

  string action = words[0];
  float delta = std::stof(words[1]);

  int x = 0, y = 0;
  if (action == "forward") {
    x = delta;
  }
  else if (action == "up") {
    y = -delta;
  }
  else if (action == "down") {
    y = delta;
  }
  else {
    throw -1;
  }
  SubPos move(x,y);
  SubPos newPos = currentPos + move;
  return newPos;
}

void run() {
  ifstream f("input.txt");

  std::string line;
  SubPos pos;
  while (getline(f, line)) {
    pos = parse(line, pos);
  }
  cout << "you are at: x=" << pos.x() << ", depth=" << pos.y() << endl;
  cout << "answer: " << pos.x() * pos.y() << endl;
}

void test() {
  SubPos a;
  SubPos b(5,5);
  SubPos z(3,5);

  SubPos c = a + b + z;
  assert(c.x() == 8);
  assert(c.y() == 10);

  SubPos p;
  p = parse("forward 5", a);
  assert(p.x() == 5);
}

int main() {
  test();
  run();
}
