#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>
#include <assert.h>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

vector<string> split_line_by_space(const string &line);
vector<string> split_line_by_comma(const string &line);

class P {
protected:
public:
  int x, y;
  P(int x, int y);
  P(const P &o);

  P operator = (const P &o);
  bool operator == (const P &o) const;
  bool operator != (const P &o) const;
  bool operator< (const P &lhs) const;
  float mag() const;
  friend std::ostream& operator<<(std::ostream& os, const P &p);
};

template <>
struct std::hash<P>
{
  std::size_t operator()(const P& p) const {
    return std::hash<int>()(p.y * 10000000 + p.x);
  }
};

class Board {
  unordered_map<P, int> counts;
public:
  void mark(const P &p);
  int count(int x, int y);

  int score();
};

P::P(int x, int y) : x(x), y(y) { };
P::P(const P &o) : x(o.x), y(o.y) { };

P P::operator = (const P &o) {
  return P(x, y);
}

bool P::operator == (const P &o) const {
  return x == o.x && y == o.y;
}

bool P::operator != (const P &o) const {
  return x != o.x || y != o.y;
}

bool P::operator< (const P &lhs) const {
  return mag() < lhs.mag();
}


float P::mag() const {
  return sqrt(x*x + y*y);
}

std::ostream& operator<<(std::ostream& os, const P &p) {
  os << p.x << "/" << p.y;
  return os;
}

class HydroLine {
  P from;
  P to;
public:
  HydroLine(P f, P t) : from(f), to(t) { }

  void draw(Board &b) {
    P vec(to.x - from.x, to.y - from.y);
    int dx = to.x == from.x ? 0 : (to.x > from.x ? 1:-1);
    int dy = to.y == from.y ? 0 : (to.y > from.y ? 1:-1);

    P cur = from;
    b.mark(cur);
    while (cur != to) {
      cur.x += dx;
      cur.y += dy;
      b.mark(cur);
    }
    //b.mark(to);
  }

};

void Board::mark(const P &p) {
  if (counts.find(p) == counts.end()) {
    counts.insert(pair<P, int>(p, 0));
  }

  (*counts.find(p)).second++;
}

int Board::count(int x, int y) {
  P p(x, y);

  auto found = counts.find(p);
  if (found == counts.end()) {
    return 0;
  }
  return found->second;
}

Board plot_hydros(vector<string> lines) {
  Board board;

  for (auto line_s : lines) {
    vector<string> parts = split_line_by_space(line_s);
    string start = parts[0];
    string end = parts[2];

    vector<string> p1_s = split_line_by_comma(start);
    vector<string> p2_s= split_line_by_comma(end);

    P p1(std::stoi(p1_s[0]), std::stoi(p1_s[1]));
    P p2(std::stoi(p2_s[0]), std::stoi(p2_s[1]));

    HydroLine line(p1, p2);
    line.draw(board);
  }
  return board;
}

int Board::score() {
  int twosOrHigher = 0;
  for (auto itr = counts.begin(); itr != counts.end(); ++itr) {
    if (itr->second >= 2) {
      twosOrHigher++;
    }
  }
  return twosOrHigher;
}

void test() {
  //assert( P(0,1) != P(1,0) );

  Board b;
  b.mark(P(0,1));
  b.mark(P(1,0));
  assert(b.count(0,1) == 1);
  assert(b.count(1,0) == 1);

  HydroLine l0(P(8,0), P(0,8));
  l0.draw(b);

  HydroLine l1(P(2,0), P(2,4));
  l1.draw(b);

  HydroLine l2(P(0,2), P(4,2));
  l2.draw(b);

  assert(b.count(2,2) == 2);
  assert(b.count(0,0) == 0);
  assert(b.count(2,0) == 1);

  Board newb = plot_hydros({
"0,9 -> 5,9",
"8,0 -> 0,8",
"9,4 -> 3,4",
"2,2 -> 2,1",
"7,0 -> 7,4",
"6,4 -> 2,0",
"0,9 -> 2,9",
"3,4 -> 1,4",
"0,0 -> 8,8",
"5,5 -> 8,2"
      });

  cout << "score: " << newb.score() << endl;
  assert(newb.score() == 12);

}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  Board newb = plot_hydros(lines);
  cout << "score: " << newb.score() << endl;
}

int main() {
  test();
  run();
}



vector<string> split_line_by_space(const string &line) {
  istringstream iss{line};

  vector<string> split((istream_iterator<string>(iss)),
                      istream_iterator<string>());
  return split;
}

vector<string> split_line_by_comma(const string &line) {
  stringstream ss(line);
  string part;
  vector<string> split;
  while (getline(ss, part, ',')) {
    split.push_back(part);
  }
  return split;
}


