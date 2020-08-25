#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int getLeastMoves(int kn, unsigned long* needAry, unsigned long* hasAry) {
  unsigned int moves = 0;

  unsigned long* tooManyAry = needAry;
  unsigned long* tooLittleAry = hasAry;
  long* tooManyIndexAry = new long[kn];
  long* tooLittleIndexAry = new long[kn];
  
  int tooManyCursor = 0;
  int tooLittleCursor = 0;
  int halfKn = kn / 2;
  int backwardIndex;

  int diff = hasAry[0] - needAry[0];
  if (diff > 0) {
    tooManyAry[tooManyCursor] = diff;
    tooManyIndexAry[tooManyCursor] = 0;
    tooManyCursor++;
  } else if (diff < 0) {
    tooLittleAry[tooLittleCursor] = diff;
    tooLittleIndexAry[tooLittleCursor] = 0;
    tooLittleCursor++;
  }

  for (int i = 1; i < kn - halfKn; i++) {
    diff = hasAry[i] - needAry[i];
    if (diff > 0) {
      tooManyAry[tooManyCursor] = diff;
      tooManyIndexAry[tooManyCursor] = i;
      tooManyCursor++;
    } else if (diff < 0) {
      tooLittleAry[tooLittleCursor] = -diff;
      tooLittleIndexAry[tooLittleCursor] = i;
      tooLittleCursor++;
    }
    
    backwardIndex = kn - i;
    if (backwardIndex > halfKn) {
      diff = hasAry[backwardIndex] - needAry[backwardIndex];
      if (diff > 0) {
        tooManyAry[tooManyCursor] = diff;
        tooManyIndexAry[tooManyCursor] = -i;
        tooManyCursor++;
      } else if (diff < 0) {
        tooLittleAry[tooLittleCursor] = -diff;
        tooLittleIndexAry[tooLittleCursor] = -i;
        tooLittleCursor++;
      }
    }
  }

  int i = 0;
  int j = 0;
  int tooManyIndex;
  int tooLittleIndex;
  int tooMany;
  int tooLittle;
  unsigned int totalMoved;
  while (
    i < tooManyCursor ||
    j < tooLittleCursor
  ) {
    tooManyIndex = tooManyIndexAry[i];
    tooLittleIndex = tooLittleIndexAry[j];
    tooMany = tooManyAry[i];
    tooLittle = tooLittleAry[j];
    totalMoved = min(tooMany, tooLittle);
    moves += min(
      abs(tooManyIndex - (kn + tooLittleIndex)),
      abs(tooManyIndex - tooLittleIndex)
    ) * totalMoved;
    tooMany -= totalMoved;
    tooLittle -= totalMoved;

    if (tooMany == 0) {
      i++;
    } else {
      tooManyAry[i] = tooMany;
    }

    if (tooLittle == 0) {
      j++;
    } else {
      tooLittleAry[j] = tooLittle;
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
//   int needAry[5] = {1,1,1,1,1};
//   int hasAry[5] = {2,3,0,0,0};
//   int leastMoves = getLeastMoves(5, needAry, hasAry);
//   cout << leastMoves << endl;
//   return 0;
// }
