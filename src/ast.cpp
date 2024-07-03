#include <string>

#include "ast.h"
#include "token.h"

// Return Statement
const void ReturnStatement::statementNode() const {}

const std::string ReturnStatement::TokenLiteral() const {
  return token.literal;
}

// Let Statement
const void LetStatement::statementNode() const {}

const std::string LetStatement::TokenLiteral() const { return token.literal; }

// Expression Statement
const void ExpressionStatement::statementNode() const {}

const std::string ExpressionStatement::TokenLiteral() const {
  return token.literal;
}

// Program
const std::string Program::TokenLiteral() const {
  if (statements.size() > 0) {
    return statements[0]->TokenLiteral();
  }
  return "";
}

// Identifier
const void Identifier::expressionNode() const {}

const std::string Identifier::TokenLiteral() const { return token.literal; }
