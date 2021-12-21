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

class LanternFish {
  int timer;
public:
  LanternFish() : timer(8) { };
  LanternFish(int t) : timer(t) { };
  LanternFish(const LanternFish &o) : timer(o.timer) { };

  bool step(vector<LanternFish *> &world) {
    timer--;
    if (timer < 0) {
      timer = 6;
      return true;
    }
    return false;
  }
};

void run_simulation(vector<LanternFish *> &fishies) {
  vector<LanternFish *> new_fish;
  for (LanternFish *fish : fishies) {
    if (fish->step(fishies)) {;
      new_fish.push_back(new LanternFish());
    }
  }

  for (auto fish : new_fish) {
    fishies.push_back(fish);
  }
}

vector<LanternFish *> parse_population(vector<string> lines) {
  vector<LanternFish *> world;
  for (auto line : lines) {
    for (auto age_s : split_line_by_comma(line)) {
      world.push_back(new LanternFish(std::stof(age_s)));
    }
  }
  return world;
}

void clear_world(vector<LanternFish *> world) {
  for (auto fish : world) {
    delete fish;
  }
}
void test() {
  vector<LanternFish *> world;
  world.push_back(new LanternFish(3));

  run_simulation(world);
  run_simulation(world);
  run_simulation(world);

  assert( world.size() == 1 );

  run_simulation(world);
  assert( world.size() == 2 );

  clear_world(world);

  vector<LanternFish *> world2 = parse_population({
      "3,4,3,1,2"
  });

  for (int i = 0; i < 18; i++) {
    run_simulation(world2);
    cout << "world size " << world2.size() << endl;
  }
  assert(world2.size() == 26);

  for (int i = 0; i < 62; i++) {
    run_simulation(world2);
    cout << "world size " << world2.size() << endl;
  }
  assert(world2.size() == 5934);

  clear_world(world2);
}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  vector<LanternFish *> world = parse_population(lines);

  for (int i = 0; i < 80; i++) {
    cout << "i=" << i << " world size " << world.size() << endl;
    run_simulation(world);
  }
  cout << "world size " << world.size() << endl;

  clear_world(world);
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


