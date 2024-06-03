#ifndef LEXER_H
#define LEXER_H

#include <cstddef>
#include <string>
#include <vector>

#include "token.h"

class Lexer {
private:
  std::string m_input;
  size_t m_position;
  size_t m_read_position;
  char m_byte;

  void readChar();
  char peekChar() const;
  std::string readNumber();
  bool isLetter(char ch) const;
  std::string readIdentifier();
  void skipWhitespace(char m_byte);
  token_type getKeyword(const std::string &word) const;

public:
  Lexer(std::string input);
  token nextToken();
  void print();
};

int lexerTest();

#endif // LEXER_H
