#include <cassert>
#include <cctype>
#include <cstddef>
#include <ctype.h>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "token.h"

class lexer {
private:
  std::string m_input;
  size_t m_position;
  size_t m_read_position;
  char m_byte;

public:
  lexer(std::string input)
      : m_input(input), m_position(0), m_read_position(1), m_byte{input[0]} {}

  void readChar() {
    if (m_read_position >= m_input.size()) {
      m_byte = 0;
    } else {
      m_byte = m_input[m_read_position];
    }
    m_position = m_read_position;
    m_read_position += 1;
  }

  bool isLetter(char byte) { return isalpha(byte) || byte == '_'; }

  std::string readIdentifier() {
    std::string word{};
    while (isLetter(m_byte)) {
      word += m_byte;
      readChar();
    }
    return word;
  };

  void skipWhitespace(char m_byte) {
    if (m_byte == ' ' || m_byte == '\n') {
      readChar();
    }
  }

  token nextToken() {
    token tok{};
    skipWhitespace(m_byte);
    switch (m_byte) {
    case '=':
      tok = token(token_type::assign, m_byte);
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
    case '{':
      tok = token(token_type::lsquirly, m_byte);
      break;
    case '}':
      tok = token(token_type::rsquirly, m_byte);
      break;
    case '\0':
      tok = token(token_type::eof, m_byte);
      break;
    default:
      if (isalpha(m_byte)) {
        std::string word = readIdentifier();
        token_type keyword = getKeyword(word);
        tok = token(keyword, word);
      } else if (isdigit(m_byte)) {
        tok = token(token_type::integer, m_byte);
      } else {
        tok = token(token_type::illegal, m_byte);
      }
      break;
    }
    readChar();
    return tok;
  }

  void print() const {
    std::cout << "\nLexer State:\n";
    std::cout << "Input: " << m_input << "\n";
    std::cout << "Position: " << m_position << "\n";
    std::cout << "Read Position: " << m_read_position << "\n";
    std::cout << "Current Byte: " << m_byte << "\n";
  }
};

int test() {
  std::string input = "let five = 5;"
                      "let ten = 10;"
                      "let add = fn(x, y) {"
                      "x + y;"
                      "};"
                      "let result = add(five, ten);";

  std::vector<token> tests{
      token(token_type::let, "let"),
      token(token_type::identifier, "five"),
      token(token_type::assign, '='),
      token(token_type::integer, '5'),
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
      token(token_type::eof, '\0'),
  };

  lexer test_lexer{lexer(input)};

  for (int i = 0; i < tests.size() - 1; i++) {
    token test_token = tests[i];
    token lexer_token = test_lexer.nextToken();

    std::cout << test_token.type << " | " << lexer_token.type << '\n';

    auto test_literal_string = std::get_if<std::string>(&test_token.literal);
    auto lexer_literal_string = std::get_if<std::string>(&lexer_token.literal);

    auto test_literal_char = std::get_if<char>(&test_token.literal);
    auto lexer_literal_char = std::get_if<char>(&lexer_token.literal);

    if (test_literal_string && lexer_literal_string) {
      std::cout << *test_literal_string << " | " << *lexer_literal_string
                << '\n';
    } else {
      std::cout << *test_literal_char << " | " << *lexer_literal_char << '\n';
    }

    std::cout << '\n';

    assert((test_token.type == lexer_token.type) &&
           "test token does not match token in lexer");

    assert(test_token.literal == lexer_token.literal &&
           "test char does not match token in lexer");
  }
  return 1;
}

int main() {
  test();
  return 0;
}
