#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <memory>
#include <string>
#include <vector>

class Parser {
private:
  Lexer m_lexer;
  Token m_curToken;
  Token m_peekToken;

  std::unique_ptr<Statement> parseLetStatement();
  std::unique_ptr<Statement> parseReturnStatement();

public:
  std::vector<std::string> m_errors{};
  Parser(Lexer lexer);
  void nextToken();
  std::unique_ptr<Statement> parseStatement();
  Program parseProgram();
  bool expectPeek(token_type t);
  void peekError(token_type t);
};

void checkParserErrors(Parser P);
void testLetStatements();
void testReturnStatements();
void testLetStatement(Statement *statement, std::string &name);

#endif // !PARSER_H
