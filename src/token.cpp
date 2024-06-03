#include "token.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

// Implement the default constructor
token::token() : type(token_type::eof), literal('\0') {}

// Implement the constructor for a token with a character literal
token::token(const token_type type, char literal)
    : type(type), literal(literal) {}

// Implement the constructor for a token with a string literal
token::token(const token_type type, std::string literal)
    : type(type), literal(literal) {}

void token::print() const {
  const int leftWidth = 12;

  auto literal_string = std::get_if<std::string>(&literal);
  auto literal_char = std::get_if<char>(&literal);

  if (literal_string) {
    std::cout << std::setw(leftWidth) << *literal_string;

  } else {
    std::cout << std::setw(leftWidth) << *literal_char;
  }
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
