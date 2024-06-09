#include <iostream>

#include "lexer.h"
#include "repl.h"

int main() {
  lexerTest();
  std::cout << "Unit Tests Passed!" << '\n';
  std::cout << "Hello! Welcome to the Monkey Programming Language REPL."
            << '\n';
  std::cout << "enter 'q' to exit" << '\n';
  Repl::start();
  return 0;
}
