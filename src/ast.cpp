#include <string>

#include "ast.h"
#include "token.h"

// Let Statement
const void LetStatement::statementNode() const {}

const std::string LetStatement::TokenLiteral() const { return token.literal; }

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
