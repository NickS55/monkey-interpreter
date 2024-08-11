#include <iostream>

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "repl.h"

int main() {
  // TODO: clean up test cases.
  // lexerTest();
  // testLetStatements();
  // testReturnStatements();
  // testString();
  // testIdentifierExpression();
  testIntegerLiteralExpression();
  std::cout << "Unit Tests Passed!" << '\n';
  std::cout << "Hello! Welcome to the Monkey Programming Language REPL."
            << '\n';
  std::cout << "enter 'q' to exit" << '\n';
  Repl::start();
  return 0;
}
