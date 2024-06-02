#ifndef TOKEN_H
#define TOKEN_H

#include <map>
#include <string>
#include <variant>

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

struct token {
  token_type type;
  std::variant<std::string, char> literal;

  token();
  token(const token_type type, char literal);
  token(const token_type type, std::string literal);
};

token_type getKeyword(std::string word);

#endif // TOKEN_H
