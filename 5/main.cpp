#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <cmath>
#include <assert.h>

using namespace std;

struct Eg {
  int epsilon;
  int gamma;
  Eg(int g, int e) : gamma(g), epsilon(e) { };
};

Eg gamma(const std::vector<string> &lines) {
  vector<int> counts(lines[0].size());

  for (auto l : lines) {
    int pos = 0;
    for (auto c : l) {
      if (pos >= counts.size()) {
        throw -1;
      }
      if (c == '1') {
        counts[pos]++;
      } else {
        counts[pos]--;
      }
      pos++;
    }
  }
  int gamma = 0;
  int epsilon = 0;
  int base = pow(2, counts.size()-1);
  for (auto bit : counts) {
    gamma += base * (bit > 0 ? 1 : 0);
    epsilon += base * (bit > 0 ? 0 : 1);
    base /= 2;
  }
  return Eg(gamma, epsilon);
}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  Eg eg = gamma(lines);
  std::cout << "gamma = " << eg.gamma << ", epsilon = " << eg.epsilon << endl;
  std::cout << "answer: " << eg.gamma * eg.epsilon << endl;
}


void test() {
  Eg t = gamma( {
"00100",
"11110",
"10110",
"10111",
"10101",
"01111",
"00111",
"11100",
"10000",
"11001",
"00010",
"01010"
      });
  std::cout << "gamma is " << t.gamma << endl;
  assert(t.gamma == 22);
  std::cout << "eps is " << t.epsilon << endl;
  assert(t.epsilon == 9);
}

int main() {
  test();
  run();
}
