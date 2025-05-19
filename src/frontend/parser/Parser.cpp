// src/frontend/parser/Parser.cpp

#include "frontend/parser/Parser.h"
#include "frontend/ast/Statement.h"
#include "frontend/ast/Expression.h"
#include "frontend/lexer/Lexer.h"

namespace zencc {

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {}

ASTNodePtr Parser::parse() {
    // Placeholder: eventually parse full program
    return parseStatement();
}

ASTNodePtr Parser::parseStatement() {
    // Placeholder logic for parsing a print statement
    if (currentToken.type == TokenType::Print) {
        advance();
        auto expr = parseExpression();
        return std::make_unique<PrintStatement>(std::move(expr));
    }
    // TODO: handle more statement types
    return nullptr;
}

ASTNodePtr Parser::parseExpression() {
    // Placeholder for literal expression parsing
    if (currentToken.type == TokenType::NumberLiteral) {
        auto value = currentToken.literal;
        advance();
        return std::make_unique<Expression>(value);
    }
    return nullptr;
}

void Parser::advance() {
    currentToken = lexer.getNextToken();
}

} // namespace zencc
