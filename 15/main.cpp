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
vector<string> split_line_by_pipe(const string &line);

map<int,int> digits = map<int,int>({
    {0,6},
    {1,2},
    {2,5},
    {3,5},
    {4,4},
    {5,5},
    {6,6},
    {7,3},
    {8,7},
    {9,6}
});

map<int,int> make_digit_count_map() {
  return map<int,int>({
      {0,0}, {1,0}, {2,0}, {3,0}, {4,0},
      {5,0}, {6,0}, {7,0}, {8,0}, {9,0}
  });
}

map<int,int> get_digits(vector<string> output) {
  map<int,int> possible_digits_counts = make_digit_count_map();
  for (auto o : output) {
    int size = o.size();

    for (map<int,int>::iterator i = digits.begin();
        i != digits.end(); i++) {
      if (i->second == size) {

        int digit = i->first;
        (*possible_digits_counts.find(digit)).second++;
      }
    }
  }
  return possible_digits_counts;
}

map<int,int> get_ons(vector<string> lines) {
  map<int,int> possible_digits = make_digit_count_map();
  for (auto line : lines) {
    vector<string> parts = split_line_by_pipe(line);
    vector<string> outputs = split_line_by_space(parts[1]);

    map<int,int> these_possible_digits = get_digits(outputs);
    for (auto &d : these_possible_digits) {
      possible_digits.find(d.first)->second += d.second;
    }
  }
  return possible_digits;
}

void test() {
  map<int,int> digit_counts = get_ons({
"be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe",
"edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc"
"fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg",
"fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb",
"aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea",
"fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb",
"dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe",
"bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef",
"egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb",
"gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce"
  });
  assert( digit_counts[1] == 6);

  assert( (digit_counts[1] + digit_counts[4] + digit_counts[7] + digit_counts[8]) == 26);
}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  map<int,int> digit_counts = get_ons(lines);
  cout << "answer: " << ( (digit_counts[1] + digit_counts[4] + digit_counts[7] + digit_counts[8])) << endl;
  /*
  auto nums_s = split_line_by_comma(lines[0]);
  vector<int> nums;
  for (string num_s : nums_s) {
    nums.push_back(std::stoi(num_s));
  }

  Result best = find_closest_distance(nums);
  cout << "best fuel=" << best.fuel << endl;
  */
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

vector<string> split_line_by_pipe(const string &line) {
  stringstream ss(line);
  string part;
  vector<string> split;
  while (getline(ss, part, '|')) {
    split.push_back(part);
  }
  return split;
}


