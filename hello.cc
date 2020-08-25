#include <iostream>

int main(int argc, char* argv[]) {
  // std::cout << argv[0] << "says hello, " << argv[1] << "!" << std::endl;
  if (argc == 1) {
    std::cout << "Hello, World!" << std::endl;
  } else {
    std::cout << "Hello, " << argv[1] << "!" << std::endl;
  }
  return 0;
}
