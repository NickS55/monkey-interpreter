#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"

Parser::Parser(Lexer lexer) : m_lexer(lexer), m_curToken(), m_peekToken() {
  nextToken();
  nextToken();

  registerPrefix(token_type::identifier,
                 [this]() { return parseIdentifier(); });
};

std::unique_ptr<Expression> Parser::parseIdentifier() {
  return std::make_unique<Identifier>(m_curToken, m_curToken.literal);
};

void Parser::registerPrefix(token_type t, prefixParseFn fn) {
  prefixParseFns.emplace(t, fn);
};

void Parser::registerInfix(token_type t, infixParseFn fn) {
  infixParseFns.emplace(t, fn);
}

void Parser::nextToken() {
  m_curToken = m_peekToken;
  m_peekToken = m_lexer.nextToken();
}

void Parser::peekError(token_type t) {
  std::ostringstream oss;
  oss << "expected next token to be " << t << ", got " << m_peekToken.type
      << " instead.";
  m_errors.push_back(oss.str().c_str());
}

bool Parser::expectPeek(token_type t) {
  if (m_peekToken.type == t) {
    nextToken();
    return true;
  }
  peekError(t);
  return false;
}

std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement() {
  auto ES = std::make_unique<ExpressionStatement>();
  ES->token = m_curToken;
  ES->expression = parseExpression(precedence::LOWEST);

  if (m_curToken.type == token_type::semicolon)
    nextToken();

  return ES;
}

std::unique_ptr<Expression> Parser::parseExpression(precedence psrecedence) {
  auto prefix = prefixParseFns.find(m_curToken.type);
  if (prefix == prefixParseFns.end()) {
    return nullptr;
  }
  auto leftExp = prefix->second();
  return leftExp;
}

std::unique_ptr<Statement> Parser::parseLetStatement() {
  std::unique_ptr<LetStatement> statement = std::make_unique<LetStatement>();

  statement->token = m_curToken;

  if (!expectPeek(token_type::identifier)) {
    return nullptr;
  }

  auto name = std::make_unique<Identifier>();
  name->token = m_curToken;
  name->value = m_curToken.literal;

  statement->name = std::move(name);

  if (!expectPeek(token_type::assign)) {
    return nullptr;
  }

  // TODO: Skipping the expression until we find a semicolon
  while (m_curToken.type != token_type::semicolon) {
    nextToken();
  }

  return statement;
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
  std::unique_ptr<ReturnStatement> statement =
      std::make_unique<ReturnStatement>();

  statement->token = m_curToken;

  // TODO: Skipping the expression until we find a semicolon
  while (m_curToken.type != token_type::semicolon) {
    nextToken();
  }

  return statement;
}

std::unique_ptr<Statement> Parser::parseStatement() {
  switch (m_curToken.type) {
  case token_type::let:
    return parseLetStatement();
  case token_type::return_T:
    return parseReturnStatement();
  default:
    return parseExpressionStatement();
  }
}

Program Parser::parseProgram() {
  Program program{};

  while (m_curToken.type != token_type::eof) {
    auto statement = parseStatement();

    if (statement) {
      program.statements.push_back(std::move(statement));
    }

    nextToken();
  }

  return program;
};

void testLetStatement(Statement *statement, std::string &name) {
  assert((statement->TokenLiteral() == "let") &&
         "dynamic_cast to LetStatement failed, letStatement is a nullptr");

  auto letStatement = dynamic_cast<LetStatement *>(statement);

  assert((letStatement->name->value == name) &&
         ("let Statement name is not correct"));

  assert((letStatement->name->TokenLiteral() == name &&
          "let statement value does not match tokenLiteral"));
};

void testLetStatements() {
  std::string input = "let x = 5;"
                      "let y = 10;"
                      "let foobar = 838383;";
  Lexer lexer(input);
  Parser parser(lexer);

  Program program{parser.parseProgram()};

  checkParserErrors(parser);

  // std::cout << program.statements.size() << '\n';
  assert((program.statements.size() != 0) && "ParseProgram() returned nil");
  assert((program.statements.size() == 3) &&
         "program.statements does not equal 3");

  std::vector<std::string> tests{"x", "y", "foobar"};

  for (int i = 0; i < tests.size(); i++) {
    auto *letStatement =
        dynamic_cast<LetStatement *>(program.statements[i].get());

    assert((letStatement) &&
           "dynamic_cast to LetStatement failed, letStatement is a nullptr");

    testLetStatement(letStatement, tests[i]);
  }
};

void testReturnStatements() {
  std::string input = "return 5;"
                      "return 10;"
                      "return 993322;";

  Lexer lexer(input);
  Parser parser(lexer);

  Program program(parser.parseProgram());

  checkParserErrors(parser);

  assert((program.statements.size() == 3) &&
         "program.statements does not equal 3");

  for (int i = 0; i < program.statements.size(); i++) {
    auto *returnStatement =
        dynamic_cast<ReturnStatement *>(program.statements[i].get());

    assert(
        (returnStatement) &&
        "dynamic_cast to returnStatement failed, returnStatement is a nullptr");

    assert(returnStatement->TokenLiteral() == "return");

    // expression parsing testing
  }
};

void checkParserErrors(Parser p) {
  int numErrors = p.m_errors.size();
  if (numErrors == 0) {
    return;
  }
  std::cout << "parser has " << numErrors << " errors.";
  for (int i = 0; i < numErrors; i++) {
    std::cout << "Parser Error: " << p.m_errors[i] << '\n';
  }
  std::exit(1);
}

void testIdentifierExpression() {
  std::string input = "foobar";

  Lexer lexer(input);
  Parser parser(lexer);
  Program program(parser.parseProgram());

  checkParserErrors(parser);

  assert(program.statements.size() == 1 &&
         "program doesn't have the correct num of statements");

  auto *statement =
      dynamic_cast<ExpressionStatement *>(program.statements[0].get());

  assert(statement && "expresstion not Expression");

  auto *identifier = dynamic_cast<Identifier *>(statement->expression.get());

  assert(identifier && "expresstion not Identifier");
  assert(identifier->value == "foobar" && "identifier's value is not foobar");
  assert(identifier->TokenLiteral() == "foobar" &&
         "identifier's token literal is not foobar");
};
