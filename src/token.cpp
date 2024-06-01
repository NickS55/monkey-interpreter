#include "token.h"
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
