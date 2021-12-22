#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <list>
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

int distance(int from, vector<int> positions) {
  int dist = 0;
  for (int pos : positions) {
    dist += abs(from - pos);
  }
  return dist;
}

struct Result {
  int pos;
  int fuel;
  Result(int pos, int fuel) : pos(pos), fuel(fuel) {};
};

Result find_closest_distance(vector<int> positions) {
  int lowest = *min_element(positions.begin(), positions.end());
  int highest = *max_element(positions.begin(), positions.end());

  int current_min = 9999999;
  int current_pos = -1;
  for (int d = lowest; d <= highest; d++) {
    int new_d = distance(d, positions);
    if (new_d < current_min) {
      current_min = new_d;
      current_pos = d;
    }
  }
  return Result(current_pos, current_min);
}


void test() {
  int d = distance(1, {
      16,1,2,0,4,2,7,1,2,14
  });

  assert(d == 41);

  Result r = find_closest_distance({
      16,1,2,0,4,2,7,1,2,14
  });
  assert(r.pos == 2);
}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  auto nums_s = split_line_by_comma(lines[0]);
  vector<int> nums;
  for (string num_s : nums_s) {
    nums.push_back(std::stoi(num_s));
  }

  Result best = find_closest_distance(nums);
  cout << "best fuel=" << best.fuel << endl;
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


