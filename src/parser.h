#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

using prefixParseFn = std::function<std::unique_ptr<Expression>()>;
using infixParseFn =
    std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>)>;

enum precedence {
  INDEX,
  LOWEST,
  EQUALS,
  SUM,
  PRODUCT,
  PREFIX,
  CALL,
};

class Parser {
private:
  Lexer m_lexer;
  Token m_curToken;
  Token m_peekToken;

  std::unique_ptr<Statement> parseLetStatement();
  std::unique_ptr<Statement> parseReturnStatement();
  std::unique_ptr<ExpressionStatement> parseExpressionStatement();

public:
  std::vector<std::string> m_errors{};
  Parser(Lexer lexer);
  void nextToken();
  std::unique_ptr<Statement> parseStatement();
  Program parseProgram();
  bool expectPeek(token_type t);
  void peekError(token_type t);
  void registerPrefix(token_type t, prefixParseFn fn);
  void registerInfix(token_type t, infixParseFn fn);
  std::unique_ptr<Expression> parseExpression(precedence precedence);
  std::unique_ptr<Expression> parseIntegerLiteral();
  std::unique_ptr<Expression> parseIdentifier();

  std::map<token_type, prefixParseFn> prefixParseFns;
  std::map<token_type, infixParseFn> infixParseFns;
};

void checkParserErrors(Parser P);
void testLetStatements();
void testReturnStatements();
void testLetStatement(Statement *statement, std::string &name);
void testIdentifierExpression();
void testIntegerLiteralExpression();

#endif // !PARSER_H
