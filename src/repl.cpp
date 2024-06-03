#include "lexer.h"
#include <iostream>
#include <string>
namespace Repl {

const std::string prompt = ">> ";
void start() {
  std::string userInput{};
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, userInput);
    if (userInput == "q") {
      break;
    }
    Lexer lexer{userInput};
    lexer.print();
  }
}

} // namespace Repl
