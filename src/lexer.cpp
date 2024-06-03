#include <cassert>
#include <cctype>
#include <ctype.h>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::string input)
    : m_input(input), m_position(0), m_read_position(1), m_byte{input[0]} {}

void Lexer::readChar() {
  if (m_read_position >= m_input.size()) {
    m_byte = 0;
  } else {
    m_byte = m_input[m_read_position];
  }
  m_position = m_read_position;
  m_read_position += 1;
}

char Lexer::peekChar() const {
  if (m_read_position >= m_input.size()) {
    return 0;
  } else {
    return m_input[m_read_position];
  }
}

std::string Lexer::readNumber() {
  std::string number{};
  do {
    number += m_byte;
    if (isdigit(peekChar())) {
      readChar();
    } else {
      break;
    }
  } while (isdigit(m_byte));

  return number;
}

bool Lexer::isLetter(char ch) const { return isalpha(ch) || ch == '_'; }

std::string Lexer::readIdentifier() {
  std::string word{};
  while (isLetter(m_byte)) {
    word += m_byte;
    if (isalpha(peekChar())) {
      readChar();
    } else {
      break;
    }
  }
  return word;
};

void Lexer::skipWhitespace(char m_byte) {
  if (m_byte == ' ' || m_byte == '\n') {
    readChar();
  }
}

token Lexer::nextToken() {
  token tok{};
  skipWhitespace(m_byte);
  switch (m_byte) {
  case '=':
    if ('=' == peekChar()) {
      readChar();
      tok = token(token_type::equal, "==");
    } else {
      tok = token(token_type::assign, m_byte);
    }
    break;
  case ';':
    tok = token(token_type::semicolon, m_byte);
    break;
  case '(':
    tok = token(token_type::lparen, m_byte);
    break;
  case ')':
    tok = token(token_type::rparen, m_byte);
    break;
  case ',':
    tok = token(token_type::comma, m_byte);
    break;
  case '+':
    tok = token(token_type::plus, m_byte);
    break;
  case '-':
    tok = token(token_type::minus, m_byte);
    break;
  case '{':
    tok = token(token_type::lsquirly, m_byte);
    break;
  case '}':
    tok = token(token_type::rsquirly, m_byte);
    break;
  case '!':
    if ('=' == peekChar()) {
      readChar();
      tok = token(token_type::not_equal, "!=");
    } else {
      tok = token(token_type::bang, m_byte);
    }
    break;
  case '<':
    tok = token(token_type::lt, m_byte);
    break;
  case '>':
    tok = token(token_type::gt, m_byte);
    break;
  case '*':
    tok = token(token_type::asterisk, m_byte);
    break;
  case '/':
    tok = token(token_type::slash, m_byte);
    break;
  case '\0':
    tok = token(token_type::eof, m_byte);
    break;
  default:
    if (isalpha(m_byte)) {
      std::string word = readIdentifier();
      token_type keyword = ::getKeyword(word);
      tok = token(keyword, word);
    } else if (isdigit(m_byte)) {
      std::string number = readNumber();
      tok = token(token_type::integer, number);
    } else {
      tok = token(token_type::illegal, m_byte);
    }
    break;
  }
  readChar();
  return tok;
}

void Lexer::print() {
  token tok{};
  while (true) {
    tok = nextToken();
    if (tok.type == token_type::eof) {
      break;
    } else {
      tok.print();
    }
  }
}

int lexerTest() {
  std::string input = "let five = 5;"
                      "let ten = 10;"
                      "let add = fn(x, y) { x + y; };"
                      "let result = add(five, ten);"
                      "!-/*5;"
                      "5 < 10 > 5;"
                      "if (5 < 10) {"
                      "return true;"
                      "} else {"
                      "return false;"
                      "}"
                      "10 == 10;"
                      "10 != 9;";

  std::vector<token> tests{
      token(token_type::let, "let"),
      token(token_type::identifier, "five"),
      token(token_type::assign, '='),
      token(token_type::integer, "5"),
      token(token_type::semicolon, ';'),
      token(token_type::let, "let"),
      token(token_type::identifier, "ten"),
      token(token_type::assign, '='),
      token(token_type::integer, "10"),
      token(token_type::semicolon, ';'),
      token(token_type::let, "let"),
      token(token_type::identifier, "add"),
      token(token_type::assign, '='),
      token(token_type::function, "fn"),
      token(token_type::lparen, '('),
      token(token_type::identifier, "x"),
      token(token_type::comma, ','),
      token(token_type::identifier, "y"),
      token(token_type::rparen, ')'),
      token(token_type::lsquirly, '{'),
      token(token_type::identifier, "x"),
      token(token_type::plus, '+'),
      token(token_type::identifier, "y"),
      token(token_type::semicolon, ';'),
      token(token_type::rsquirly, '}'),
      token(token_type::semicolon, ';'),
      token(token_type::let, "let"),
      token(token_type::identifier, "result"),
      token(token_type::assign, '='),
      token(token_type::identifier, "add"),
      token(token_type::lparen, '('),
      token(token_type::identifier, "five"),
      token(token_type::comma, ','),
      token(token_type::identifier, "ten"),
      token(token_type::rparen, ')'),
      token(token_type::semicolon, ';'),
      token(token_type::bang, '!'),
      token(token_type::minus, '-'),
      token(token_type::slash, '/'),
      token(token_type::asterisk, '*'),
      token(token_type::integer, "5"),
      token(token_type::semicolon, ';'),
      token(token_type::integer, "5"),
      token(token_type::lt, '<'),
      token(token_type::integer, "10"),
      token(token_type::gt, '>'),
      token(token_type::integer, "5"),
      token(token_type::semicolon, ';'),
      token(token_type::if_T, "if"),
      token(token_type::lparen, '('),
      token(token_type::integer, "5"),
      token(token_type::lt, '<'),
      token(token_type::integer, "10"),
      token(token_type::rparen, ')'),
      token(token_type::lsquirly, '{'),
      token(token_type::return_T, "return"),
      token(token_type::true_T, "true"),
      token(token_type::semicolon, ';'),
      token(token_type::rsquirly, '}'),
      token(token_type::else_T, "else"),
      token(token_type::lsquirly, '{'),
      token(token_type::return_T, "return"),
      token(token_type::false_T, "false"),
      token(token_type::semicolon, ';'),
      token(token_type::rsquirly, '}'),
      token(token_type::integer, "10"),
      token(token_type::equal, "=="),
      token(token_type::integer, "10"),
      token(token_type::semicolon, ';'),
      token(token_type::integer, "10"),
      token(token_type::not_equal, "!="),
      token(token_type::integer, "9"),
      token(token_type::semicolon, ';'),
      token(token_type::eof, '\0'),
  };

  Lexer test_lexer{Lexer(input)};

  for (int i = 0; i < tests.size(); i++) {
    token test_token = tests[i];
    token lexer_token = test_lexer.nextToken();

    // ~~~ debugging ~~~

    // std::cout << "test"
    //           << " | "
    //           << "input" << '\n';
    // std::cout << test_token.type << " | " << lexer_token.type << '\n';
    // auto test_literal_string =
    // std::get_if<std::string>(&test_token.literal); auto
    // lexer_literal_string = std::get_if<std::string>(&lexer_token.literal);
    //
    // auto test_literal_char = std::get_if<char>(&test_token.literal);
    // auto lexer_literal_char = std::get_if<char>(&lexer_token.literal);
    //
    // if (test_literal_string && lexer_literal_string) {
    //   std::cout << *test_literal_string << " | " << *lexer_literal_string
    //             << '\n';
    // } else {
    //   std::cout << *test_literal_char << " | " << *lexer_literal_char <<
    //   '\n';
    // }
    //
    // std::cout << '\n';

    assert((test_token.type == lexer_token.type) &&
           "test token does not match token in lexer");

    assert(test_token.literal == lexer_token.literal &&
           "test char does not match token in lexer");
  }
  return 1;
}
