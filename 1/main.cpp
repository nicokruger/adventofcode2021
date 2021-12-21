#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  cout << "hi" << endl;
  ifstream f("data.txt");

  std::string line;
  float num, prevnum = 99999999;
  int count = 0;
  while (getline(f, line)) {
    num = std::stof(line);
    //cout << num << endl;
    if (num > prevnum) {
      count++;
    }
    prevnum = num;
  }
  cout << "total: " << count << endl;
}
