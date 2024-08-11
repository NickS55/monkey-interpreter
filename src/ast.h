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
  virtual std::string string() const = 0;
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
  explicit Program(std::vector<std::unique_ptr<Statement>> &&statements);
  std::string string() const override;
  const std::string TokenLiteral() const override;
  std::vector<std::unique_ptr<Statement>> statements{};
};

class Identifier : public Expression {
public:
  Identifier(){};
  Identifier(Token token, const std::string value);

  Token token{};
  std::string value{};

  std::string string() const override;
  const void expressionNode() const;
  const std::string TokenLiteral() const override;
};

class LetStatement : public Statement {
public:
  LetStatement() = default;
  LetStatement(std::unique_ptr<Identifier> name,
               std::unique_ptr<Expression> value);
  Token token{};
  std::unique_ptr<Identifier> name{};
  std::unique_ptr<Expression> value{};
  std::string string() const override;
  const void statementNode() const;
  const std::string TokenLiteral() const override;
};

class ReturnStatement : public Statement {
public:
  Token token{};

  std::unique_ptr<Expression> returnValue{};
  std::string string() const override;
  const void statementNode() const;
  const std::string TokenLiteral() const override;
};

class ExpressionStatement : public Statement {
public:
  Token token{};
  std::unique_ptr<Expression> expression{};
  std::string string() const override;
  const void statementNode() const;
  const std::string TokenLiteral() const override;
};

class IntegerLiteral : public Expression {
public:
  IntegerLiteral() = default;
  IntegerLiteral(Token token, const int value);
  virtual ~IntegerLiteral() = default;

  Token token{};
  int value;

  std::string string() const override;
  const void expressionNode() const;
  const std::string TokenLiteral() const override;
};

void testString();

#endif // AST_H
