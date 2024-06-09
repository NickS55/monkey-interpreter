#include <cassert>
#include <cctype>
#include <ctype.h>
#include <string>
// #include <iostream>
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

Token Lexer::nextToken() {
  Token tok{};
  skipWhitespace(m_byte);
  switch (m_byte) {
  case '=':
    if ('=' == peekChar()) {
      readChar();
      tok = Token(token_type::equal, "==");
    } else {
      tok = Token(token_type::assign, std::string(1, m_byte));
    }
    break;
  case ';':
    tok = Token(token_type::semicolon, std::string(1, m_byte));
    break;
  case '(':
    tok = Token(token_type::lparen, std::string(1, m_byte));
    break;
  case ')':
    tok = Token(token_type::rparen, std::string(1, m_byte));
    break;
  case ',':
    tok = Token(token_type::comma, std::string(1, m_byte));
    break;
  case '+':
    tok = Token(token_type::plus, std::string(1, m_byte));
    break;
  case '-':
    tok = Token(token_type::minus, std::string(1, m_byte));
    break;
  case '{':
    tok = Token(token_type::lsquirly, std::string(1, m_byte));
    break;
  case '}':
    tok = Token(token_type::rsquirly, std::string(1, m_byte));
    break;
  case '!':
    if ('=' == peekChar()) {
      readChar();
      tok = Token(token_type::not_equal, "!=");
    } else {
      tok = Token(token_type::bang, std::string(1, m_byte));
    }
    break;
  case '<':
    tok = Token(token_type::lt, std::string(1, m_byte));
    break;
  case '>':
    tok = Token(token_type::gt, std::string(1, m_byte));
    break;
  case '*':
    tok = Token(token_type::asterisk, std::string(1, m_byte));
    break;
  case '/':
    tok = Token(token_type::slash, std::string(1, m_byte));
    break;
  case '\0':
    tok = Token(token_type::eof, std::string(0, m_byte));
    break;
  default:
    if (isalpha(m_byte)) {
      std::string word = readIdentifier();
      token_type keyword = ::getKeyword(word);
      tok = Token(keyword, word);
    } else if (isdigit(m_byte)) {
      std::string number = readNumber();
      tok = Token(token_type::integer, number);
    } else {
      tok = Token(token_type::illegal, std::string(1, m_byte));
    }
    break;
  }
  readChar();
  return tok;
}

void Lexer::print() {
  Token tok{};
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

  std::vector<Token> tests{
      Token(token_type::let, "let"),
      Token(token_type::identifier, "five"),
      Token(token_type::assign, "="),
      Token(token_type::integer, "5"),
      Token(token_type::semicolon, ";"),
      Token(token_type::let, "let"),
      Token(token_type::identifier, "ten"),
      Token(token_type::assign, "="),
      Token(token_type::integer, "10"),
      Token(token_type::semicolon, ";"),
      Token(token_type::let, "let"),
      Token(token_type::identifier, "add"),
      Token(token_type::assign, "="),
      Token(token_type::function, "fn"),
      Token(token_type::lparen, "("),
      Token(token_type::identifier, "x"),
      Token(token_type::comma, ","),
      Token(token_type::identifier, "y"),
      Token(token_type::rparen, ")"),
      Token(token_type::lsquirly, "{"),
      Token(token_type::identifier, "x"),
      Token(token_type::plus, "+"),
      Token(token_type::identifier, "y"),
      Token(token_type::semicolon, ";"),
      Token(token_type::rsquirly, "}"),
      Token(token_type::semicolon, ";"),
      Token(token_type::let, "let"),
      Token(token_type::identifier, "result"),
      Token(token_type::assign, "="),
      Token(token_type::identifier, "add"),
      Token(token_type::lparen, "("),
      Token(token_type::identifier, "five"),
      Token(token_type::comma, ","),
      Token(token_type::identifier, "ten"),
      Token(token_type::rparen, ")"),
      Token(token_type::semicolon, ";"),
      Token(token_type::bang, "!"),
      Token(token_type::minus, "-"),
      Token(token_type::slash, "/"),
      Token(token_type::asterisk, "*"),
      Token(token_type::integer, "5"),
      Token(token_type::semicolon, ";"),
      Token(token_type::integer, "5"),
      Token(token_type::lt, "<"),
      Token(token_type::integer, "10"),
      Token(token_type::gt, ">"),
      Token(token_type::integer, "5"),
      Token(token_type::semicolon, ";"),
      Token(token_type::if_T, "if"),
      Token(token_type::lparen, "("),
      Token(token_type::integer, "5"),
      Token(token_type::lt, "<"),
      Token(token_type::integer, "10"),
      Token(token_type::rparen, ")"),
      Token(token_type::lsquirly, "{"),
      Token(token_type::return_T, "return"),
      Token(token_type::true_T, "true"),
      Token(token_type::semicolon, ";"),
      Token(token_type::rsquirly, "}"),
      Token(token_type::else_T, "else"),
      Token(token_type::lsquirly, "{"),
      Token(token_type::return_T, "return"),
      Token(token_type::false_T, "false"),
      Token(token_type::semicolon, ";"),
      Token(token_type::rsquirly, "}"),
      Token(token_type::integer, "10"),
      Token(token_type::equal, "=="),
      Token(token_type::integer, "10"),
      Token(token_type::semicolon, ";"),
      Token(token_type::integer, "10"),
      Token(token_type::not_equal, "!="),
      Token(token_type::integer, "9"),
      Token(token_type::semicolon, ";"),
      Token(token_type::eof, "\0"),
  };

  Lexer test_lexer{Lexer(input)};

  for (int i = 0; i < tests.size(); i++) {
    Token test_token = tests[i];
    Token lexer_token = test_lexer.nextToken();

    // ~~~ debugging ~~~

    // std::cout << "test"
    //           << " | "
    //           << "input" << '\n';
    // std::cout << test_token.type << " | " << lexer_token.type << '\n';
    // auto test_literal_string = std::get_if<std::string>(&test_token.literal);
    // auto lexer_literal_string =
    // std::get_if<std::string>(&lexer_token.literal);
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

    assert((test_token.type == lexer_token.type) &&
           "test token does not match token in lexer");

    assert(test_token.literal == lexer_token.literal &&
           "test char does not match token in lexer");
  }
  return 1;
}
