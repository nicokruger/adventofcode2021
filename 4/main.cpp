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

  int x() const { return _x; }
  int y() const { return _y; }


};

class Sub {
  SubPos pos;
  int aim;
public:
  Sub() : pos(0,0), aim(0) { }
  Sub(const SubPos &p, int aim) : pos(p), aim(aim) {};
  Sub(const Sub &a) : pos(a.pos), aim(a.aim) { };

  Sub operator * (int aim) const {
    Sub s(this->pos, this->aim + aim);
    return s;
  }
  Sub operator + (int v) const {
    int x = pos.x() + v;
    int y = pos.y() + aim * v;
    return Sub(SubPos(x,y), aim);
  }

  Sub &operator *= (int aim) {
    Sub s(*this * aim);
    this->pos = s.pos;
    this->aim = s.aim;
    return *this;
  }
  Sub &operator += (int v) {
    Sub s(*this + v);
    this->pos = s.pos;
    this->aim = s.aim;
    return *this;
  }

  SubPos p() {
    return pos;
  }

};


Sub parse(const string &line, Sub currentSub) {

  istringstream iss{line};

  vector<string> words((istream_iterator<string>(iss)),
                       istream_iterator<string>());

  assert(words.size() == 2);

  string action = words[0];
  float delta = std::stof(words[1]);

  if (action == "forward") {
    currentSub += delta;
  }
  else if (action == "up") {
    currentSub *= -delta;
  }
  else if (action == "down") {
    currentSub *= delta;
  }
  else {
    throw -1;
  }
  return currentSub;
}

void run() {
  ifstream f("input.txt");

  std::string line;
  Sub sub;
  while (getline(f, line)) {
    sub = parse(line, sub);
  }
  cout << "you are at: x=" << sub.p().x() << ", depth=" << sub.p().y() << endl;
  cout << "answer: " << sub.p().x() * sub.p().y() << endl;
}

void test() {
  SubPos a;
  SubPos b(5,5);
  SubPos z(3,5);

  SubPos c = a + b + z;
  assert(c.x() == 8);
  assert(c.y() == 10);

  Sub s;
  s += 5;
  assert(s.p().x() == 5);

  s *= 5;
  s += 5;
  assert(s.p().x() == 10);
  assert(s.p().y() == 25);

  Sub ss;
  ss = parse("forward 5", ss);
  assert(ss.p().x() == 5);


}

int main() {
  test();
  run();
}
