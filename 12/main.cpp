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

class LanternFish {
  map<int, long> pop;
private:
  void fill(map<int,long> &p) {
    for (int i = 0; i <= 8; i++) {
      if (p.find(i) == p.end()) {
        p.insert(pair<int,long>(i, 0));
      }

    }
  }
  void print() {
    cout << "pop=" << population() << "; ";
    for(map<int, long>::iterator it = pop.begin();
        it != pop.end(); it++) {
      std::cout << it->second << ",";
    }
    cout << endl;
  }
public:
  LanternFish(vector<string> lines) {
   fill(pop);

   for (auto line : lines) {
    for (auto age_s : split_line_by_comma(line)) {
      int age = std::stof(age_s);
      pop[age]++;
    }

  }

 }

  LanternFish(map<int,long> pop) : pop(pop) {
    fill(pop);
  };

  void step() {
    map<int, long> newPop;
    fill(newPop);

    long newFish = 0;
    for (auto pairs : pop) {
      int newAge = pairs.first - 1;
      if (newAge < 0) {
        newPop[6] += pairs.second;
        newFish = pairs.second;
      } else {
        newPop[newAge] += pairs.second;
      }
    }

    newPop[8] = newFish;

    pop = newPop;

    //cout << "------------------" << endl;
    //cout << "   newFish=" << newFish << " 6pop=" << pop[6]<< endl;
    //print();
    //cout << "------------------" << endl;
  }

  long population() {
    long total = 0;
    for (auto p : pop) {
      total += p.second;
    }
    return total;
  }
};

void test() {
  LanternFish fish((map<int,long>){
      {0,10},
      {1,10},
  });

  assert( fish.population() == 20 );
  fish.step();
  assert( fish.population() == 30 );


  LanternFish fish2 = LanternFish((vector<string>){
      "3,4,3,1,2"
  });

  for (int i = 0; i < 18; i++) {
    fish2.step();
  }
  assert(fish2.population() == 26);

  for (int i = 0; i < 62; i++) {
    fish2.step();
  }
  assert(fish2.population() == 5934);

  LanternFish fish3 = LanternFish((vector<string>){
      "3,4,3,1,2"
  });

  for (int i = 0; i < 256; i++) {
    fish3.step();
  }
  assert(fish3.population() == 26984457539);


}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  LanternFish fish(lines);
  for (int i = 0; i < 256; i++) {
    fish.step();
  }
  cout << "population=" << fish.population() << endl;

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


