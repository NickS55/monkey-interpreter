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
      {"fn", token_type::function},
      {"let", token_type::let},
  };
  auto keyword{keywords.find(word)};

  if (keyword == keywords.end()) {
    return token_type::identifier;
  }

  return keyword->second;
}
