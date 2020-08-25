#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int getNthBackward(int kn, int i, int n) {
  int index = i - n;
  return index < 0 ? kn + index : index;
}

int getNthForward(int kn, int i, int n) {
  int index = i + n;
  return index >= kn ? index - kn : index;
}

int getLeastMoves(int kn, unsigned long* needAry, unsigned long* hasAry) {
  unsigned long moves = 0;
  for (int i = 0; i < kn; i++) {
    unsigned long tooMuch = hasAry[i] - needAry[i];
    while (tooMuch > 0) {
      for (int n = 1; n < ceil(kn / 2.0); n++) {
        int index = getNthBackward(kn, i, n);
        unsigned long tooLittle = hasAry[index] - needAry[index];
        if (tooLittle >= 0) {
          index = getNthForward(kn, i, n);
          tooLittle = hasAry[index] - needAry[index];
        }
        if (tooLittle < 0) {
          int totalMoved = fmin(tooMuch, -tooLittle);
          moves += n * totalMoved;
          hasAry[i] -= totalMoved;
          hasAry[index] += totalMoved;
          tooMuch -= totalMoved;
          break;
        }
      }
    }
  }
  return moves;
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    ifstream inputfile (argv[1]);
    string line;
    string numberString;
    int kn;
    vector<unsigned long> needVector;
    vector<unsigned long> hasVector;
    if (inputfile.is_open()) {
      if (getline(inputfile, line)) {
        kn = stoi(line);
      } else {
        cout << "Pass number of knights"; 
      }
      if (getline(inputfile, line)) {
        istringstream ss (line);
        while (getline(ss, numberString, ' ')) {
          needVector.push_back(stoi(numberString));
        }
      } else {
        cout << "Pass kg of food each knight needs"; 
      }
      if (getline(inputfile, line)) {
        istringstream ss (line);
        while (getline(ss, numberString, ' ')) {
          hasVector.push_back(stoi(numberString));
        }

        clock_t begin_time = clock();
        unsigned int leastMoves = getLeastMoves(5, needVector.data(), hasVector.data());
        cout << "least amount of moves: " << leastMoves << endl;
        cout << "time elapsed: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s"  << endl;
        cout << "knights: " << kn << endl;
        cout << "need array size: " << needVector.size() << endl;
        cout << "has array size: " << hasVector.size() << endl;
      } else {
        cout << "Pass kg of food each knight has"; 
      }
    }
    else {
      cout << "Unable to open file"; 
    }
  } else {
    cout << "Please provide an input file!" << endl;
  }
  return 0;
}

// int main(int argc, char* argv[]) {
//   unsigned long needAry[5] = {1,1,1,1,1};
//   unsigned long hasAry[5] = {2,3,0,0,0};
//   unsigned long leastMoves = getLeastMoves(5, needAry, hasAry);
//   std::cout << leastMoves << std::endl;
//   return 0;
// }
