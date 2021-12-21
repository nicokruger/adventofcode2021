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

using namespace std;

vector<string> split_line_by_space(const string &line);
vector<string> split_line_by_comma(const string &line);

class BingoBoard {
  int *board;
  bool *marked;
  int width, height;
public:
  BingoBoard(vector<string> board_lines) {

    board_lines.erase(
        std::remove_if( board_lines.begin(), board_lines.end(), [](string const &s) { return s.size() == 0; }),
        board_lines.end()
    );

    int w = split_line_by_space(board_lines[0]).size();
    int h = board_lines.size();

    width = w;
    height = h;

    board = new int[width * height];
    std::fill(board, board + (width * height), 0);
    marked = new bool[width * height];
    std::fill(marked, marked + (width * height), false);

    int pos = 0;
    for (auto line : board_lines) {
      vector<string> parts = split_line_by_space(line);

      for (auto part : parts) {
        board[pos++] = std::stoi(part);
      }

    }

  }

  BingoBoard(const BingoBoard &b) {
    width = b.width;
    height = b.height;

    board = new int[width * height];
    marked = new bool[width * height];

    for (int i = 0; i < width * height; i++) {
      board[i] = b.board[i];
      marked[i] = b.marked[i];
    }
  }

  BingoBoard operator = (const BingoBoard &b) {
    return BingoBoard(b);
  }

  ~BingoBoard() {
    delete [] board;
    delete [] marked;
  }

  bool play(int num) {
    for (int i = 0; i < width * height; i++) {
      if (board[i] == num) {
        marked[i] = true;

        int y = i / width;
        int x = i - y * width;
        return check_win(x,y);
      }
    }
    return false;
  }

  int check_win(int x, int y) {
    // check row
    bool won = true;
    for (int _x = 0; _x < width; _x++) {
      won = won && is_marked(_x, y);
    }

    if (won) {
      return won;
    }

    // check column
    won = true;
    for (int _y = 0; _y < height; _y++) {
      won = won && is_marked(x, _y);
    }

    return won;
  }

  int peek(int x, int y) {
    return board[y * width + x];
  }

  int score() {
    int sum = 0;
    for (int i = 0; i < width * height; i++) {
      if (!marked[i]) sum += board[i];
    }
    return sum;
  }

  bool is_marked(int x, int y) {
    return marked[y * width + x];
  }

  int w() {
    return width;
  }
  int h() {
    return height;
  }
};



vector<BingoBoard> get_boards(vector<string> lines) {
  vector<BingoBoard> boards;
  int mode = 0;

  vector<string>::iterator start = lines.begin();
  vector<string>::iterator end;

  while (start != lines.end()) {
    end = start;
    while (end != lines.end() && end->size() > 0) {
      end++;
    }

    if (end == lines.end()) {
      end = lines.end() - 1;
    }
    vector<string> board;
    copy(start, end+1, back_inserter(board));
    boards.push_back(BingoBoard(board));

    start = end;
    start++;
  }
  return boards;
}

vector<int> play_boards(vector<BingoBoard> &boards, int num) {
  vector<int> wons;
  for (int i = 0; i < boards.size(); i++) {
    bool won = boards[i].play(num);
    if (won) {
      wons.push_back(i);
    }
  }
  return wons;
}

struct BingoResult {
  int winningMove;
  int winningBoard;
  int winningScore;
  BingoResult(int move, int board, int score) : winningMove(move), winningBoard(board), winningScore(score) {};
};

BingoResult play_a_bunch_of_bingo(vector<string> lines) {
  string plays_line = lines[0];

  vector<string> boards_lines;
  copy(lines.begin() + 2, lines.end(), back_inserter(boards_lines));

  vector<BingoBoard> boards = get_boards(boards_lines);

  BingoResult lastResult(-1,-1,-1);
  vector<string> plays = split_line_by_comma(plays_line);

  set<int> wonBoards;
  for (auto play : plays) {
    int num = std::stoi(play);
    for (auto winner : play_boards(boards, num)) {
      cout << "play: " << num << ", winner=" << winner << endl;
      if (winner != -1) {
        wonBoards.insert(winner);
        if (wonBoards.size() == boards.size()) {
          cout << "last win: " << num << ", " << winner << ", " << boards[winner].score() << endl;
          return BingoResult(num, winner, boards[winner].score());
        }
      }
    };
  }
  return BingoResult(-1, -1, -1);
}

void test() {
  BingoResult result = play_a_bunch_of_bingo({
"7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
"",
"22 13 17 11  0",
 "8  2 23  4 24",
"21  9 14 16  7",
 "6 10  3 18  5",
 "1 12 20 15 19",
"",
 "3 15  0  2 22",
 "9 18 13 17  5",
"19  8  7 25 23",
"20 11 10 24  4",
"14 21 16 12  6",
"",
"14 21 17 24  4",
"10 16 15  9 19",
"18  8 23 26 20",
"22 11 13  6  5",
 "2  0 12  3  7"
  });
  int winner = result.winningBoard;
  assert( winner == 1 );

  assert(result.winningMove == 13);
  cout << "score: " << result.winningScore << endl;
  assert(result.winningScore == 148);
}

void run() {
  ifstream f("input.txt");

  std::vector<string> lines;
  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }


  BingoResult result = play_a_bunch_of_bingo(lines);

  std::cout << "winner: " << result.winningBoard << " ,move=" << result.winningMove << ", score=" << result.winningScore << endl;
  std::cout << "answer: " << result.winningScore * result.winningMove << endl;

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


