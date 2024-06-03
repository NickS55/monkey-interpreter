#include <iostream>

#include "lexer.h"
#include "repl.h"

int main() {
  std::cout << "Hello! Welcome to the Monkey Programming Language REPL."
            << '\n';
  std::cout << "exit (q)" << '\n';
  lexerTest();
  Repl::start();
  return 0;
}
