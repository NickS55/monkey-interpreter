#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "ast.h"
#include "token.h"

// Program
Program::Program(std::vector<std::unique_ptr<Statement>> &&statements)
    : statements(std::move(statements)){};

const std::string Program::TokenLiteral() const {
  if (statements.size() > 0) {
    return statements[0]->TokenLiteral();
  }
  return "";
}

std::string Program::string() const {
  std::stringstream SS;
  for (const auto &statement : statements)
    SS << statement->string();
  return SS.str();
}

// Identifier
Identifier::Identifier(Token token, const std::string value)
    : token(token), value(value){};

const void Identifier::expressionNode() const {}

const std::string Identifier::TokenLiteral() const { return token.literal; }

std::string Identifier::string() const {
  std::stringstream SS;
  SS << value;
  return SS.str();
}

// Return Statement
const void ReturnStatement::statementNode() const {}

const std::string ReturnStatement::TokenLiteral() const {
  return token.literal;
}

std::string ReturnStatement::string() const {
  std::stringstream SS;
  SS << TokenLiteral() << " ";
  // TODO: remove nill checks when expressions are added
  if (returnValue)
    SS << returnValue->string();
  SS << ";";
  return SS.str();
}

// Let Statement
LetStatement::LetStatement(std::unique_ptr<Identifier> name,
                           std::unique_ptr<Expression> value)
    : name(std::move(name)), value(std::move(value)) {
  token = Token();
  token.literal = "let";
  token.type = token_type::let;
}

const void LetStatement::statementNode() const {}

const std::string LetStatement::TokenLiteral() const { return token.literal; }

std::string LetStatement::string() const {
  std::stringstream SS;
  SS << TokenLiteral() << " ";
  SS << name->string();
  SS << " = ";
  // TODO: remove nill checks when expressions are added
  if (value)
    SS << value->string();
  SS << ";";
  return SS.str();
}

// Expression Statement
const void ExpressionStatement::statementNode() const {}

const std::string ExpressionStatement::TokenLiteral() const {
  return token.literal;
}

std::string ExpressionStatement::string() const {
  std::stringstream SS;
  // TODO: remove nill checks when expressions are added
  if (expression)
    SS << expression->string();
  return SS.str();
}

// Constructor implementation
IntegerLiteral::IntegerLiteral(Token token, const int value)
    : token(token), value(value) {}

// Implementation of virtual function string()
std::string IntegerLiteral::string() const { return std::to_string(value); }

// Implementation of virtual function expressionNode()
const void IntegerLiteral::expressionNode() const {
  // Function implementation (assuming it doesn't need to return anything)
}

// Implementation of virtual function TokenLiteral()
const std::string IntegerLiteral::TokenLiteral() const { return token.literal; }

void testString() {
  std::vector<std::unique_ptr<Statement>> statements{};

  statements.push_back(std::make_unique<LetStatement>(
      std::make_unique<Identifier>(Token(token_type::identifier, "myVar"),
                                   "myVar"),
      std::make_unique<Identifier>(Token(token_type::identifier, "anotherVar"),
                                   "anotherVar")));

  auto program = std::make_unique<Program>(std::move(statements));

  assert(program->string() == "let myVar = anotherVar;" &&
         "Program string method is not working correctly");
};
