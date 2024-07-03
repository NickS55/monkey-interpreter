#ifndef AST_H
#define AST_H

#include "token.h"
#include <memory>
#include <string>
#include <vector>

class Node {
public:
  virtual ~Node() = default;
  virtual const std::string TokenLiteral() const = 0;
};

// Expressions Produce Values
class Expression : public Node {
public:
  virtual ~Expression() = default;
};

// Statements do not Produce Values
class Statement : public Node {
public:
  virtual ~Statement() = default;
};

class Program : public Node {

public:
  Program() = default;
  const std::string TokenLiteral() const override;
  std::vector<std::unique_ptr<Statement>> statements{};
};

class Identifier : public Expression {
public:
  Identifier(){};
  Identifier(Token token, std::string &value) : token(token), value(value){};
  Token token{};
  std::string value{};
  const void expressionNode() const;
  const std::string TokenLiteral() const override;
};

class LetStatement : public Statement {
public:
  Token token{};
  std::unique_ptr<Identifier> name{};
  std::unique_ptr<Expression> value{};
  const void statementNode() const;
  const std::string TokenLiteral() const override;
};

class ReturnStatement : public Statement {
public:
  Token token{};
  std::unique_ptr<Expression> returnValue{};
  const void statementNode() const;
  const std::string TokenLiteral() const override;
};

class ExpressionStatement : public Statement {
public:
  Token token{};
  std::unique_ptr<Expression> expression{};
  const void statementNode() const;
  const std::string TokenLiteral() const override;
};

#endif // AST_H
