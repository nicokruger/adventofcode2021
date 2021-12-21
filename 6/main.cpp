#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <cmath>
#include <assert.h>

using namespace std;

struct LifeSupport {
  int oxygen;
  int co2;
  LifeSupport(int o, int c) : oxygen(o), co2(c) { };
};

int binary_string_to_decimal(const std::string &line) {
  int base = pow(2, line.size()-1);

  int val = 0;
  for (auto bit : line) {
    val += base * (bit == '1' ? 1 : 0);
    base /= 2;
  }

  return val;

}

int bitcriteria(const std::vector<string> &lines, int bit, bool (*checker)(char bit, int bitDelta) ) {
  //cout << "bit " << bit << " lines " << lines.size() << endl;

  if (lines.size() == 0) {
    std::cout << "should not be empty" << std::endl;
    throw -1;
  }
  if (lines.size() == 1) {
    return binary_string_to_decimal(lines[0]);
  }

  if (bit >= lines[0].size()) {
    std::cout << "ran out of bits" << endl;
    return -1;
  }

  int count = 0;
  //vector<int> counts(lines[0].size());

  for (auto l : lines) {
    char c = l[bit];
    if (c == '1') {
      count++;
    } else {
      count--;
    }
  }

  vector<string> filtered;
  for (auto line : lines) {
    char this_bit = line[bit];
    bool passed = checker(this_bit, count);

    //std::cout << "   line=" << line << " this_bit=" << this_bit << " passed=" << passed << endl;
    if (passed) {
      filtered.push_back(line);
    }
  }

  //cout << "count " << count << endl;
  return bitcriteria(filtered, bit + 1, checker);
}

bool oxygen_criteria(char bit, int bitDelta) {
  return bit == ((bitDelta >= 0) ? '1' : '0');
}

bool co2_criteria(char bit, int bitDelta) {
  return bit == ((bitDelta < 0) ? '1' : '0');
}


void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  int oxygen = bitcriteria(lines, 0, oxygen_criteria);
  int co2 = bitcriteria(lines, 0, co2_criteria);

  std::cout << "oxygen=" << oxygen << ", co2= " << co2 << endl;
  std::cout << "answer=" << (oxygen * co2) << endl;

}


void test() {
  int t1 = binary_string_to_decimal("10111");
  assert( t1 == 23 );
  int t2 = binary_string_to_decimal("01010");
  assert (t2 == 10 );

  int test = bitcriteria(
    {
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
    },
    0,
    oxygen_criteria
  );

  std::cout << "test= " << test << endl;
  assert( test == 23 );


  int test2 = bitcriteria(
    {
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
    },
    0,
    co2_criteria
  );

  std::cout << "test2= " << test2 << endl;
  assert( test2 == 10 );

  /*
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
  */
}

int main() {
  test();
  run();
}
