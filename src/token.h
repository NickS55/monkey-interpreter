#ifndef TOKEN_H
#define TOKEN_H

#include <map>
#include <string>

enum token_type {
  illegal,
  eof,
  identifier,
  integer,
  assign,
  plus,
  minus,
  bang,
  slash,
  asterisk,
  lt,
  gt,
  comma,
  semicolon,
  lparen,
  rparen,
  lsquirly,
  rsquirly,
  function,
  let,
  if_T,
  else_T,
  return_T,
  true_T,
  false_T,
  equal,
  not_equal,
};

struct Token {
  token_type type;
  std::string literal;

  Token();
  Token(const token_type type, char literal);
  Token(const token_type type, std::string literal);

  void print() const;
};

token_type getKeyword(std::string word);

#endif // TOKEN_H
