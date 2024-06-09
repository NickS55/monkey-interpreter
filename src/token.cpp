#include "token.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

// Implement the default constructor
Token::Token() : type(token_type::eof), literal("\0") {}

// Implement the constructor for a token with a character literal
Token::Token(const token_type type, std::string literal)
    : type(type), literal(literal) {}

void Token::print() const {
  const int leftWidth = 12;

  std::cout << std::setw(leftWidth) << literal;
  std::cout << " | " << type << '\n';
}

token_type getKeyword(std::string word) {
  std::map<std::string, token_type> keywords = {
      {"fn", token_type::function},     {"let", token_type::let},
      {"true", token_type::true_T},     {"false", token_type::false_T},
      {"if", token_type::if_T},         {"else", token_type::else_T},
      {"return", token_type::return_T},
  };

  auto keyword{keywords.find(word)};

  if (keyword == keywords.end()) {
    return token_type::identifier;
  }

  return keyword->second;
}
