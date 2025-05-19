#include "Parser.h"
#include <stdexcept>
#include <iostream>

namespace zencc {
namespace frontend {
namespace parser {

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), currentPos(0) {}

std::unique_ptr<ASTNode> Parser::parse() {
    auto ast = parseStatement();
    expect(TokenType::EndOfFile); // Ensure the input ends correctly
    return ast;
}

Token Parser::currentToken() {
    if (currentPos < tokens.size()) {
        return tokens[currentPos];
    }
    return Token(TokenType::EndOfFile, "", 0, 0); // Return EOF if out of range
}

Token Parser::consume() {
    Token token = currentToken();
    if (currentPos < tokens.size()) {
        currentPos++;
    }
    return token;
}

bool Parser::match(TokenType type) {
    if (currentToken().type == type) {
        consume();
        return true;
    }
    return false;
}

void Parser::expect(TokenType type) {
    if (!match(type)) {
        throw std::runtime_error("Unexpected token: " + currentToken().value);
    }
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    // Simplified for an arithmetic expression example (extend this)
    auto left = parseTerm();
    while (match(TokenType::Operator)) {
        Token op = consume();
        auto right = parseTerm();
        // Combine left, operator, and right into a new ASTNode (BinaryOperator, for example)
        left = std::make_unique<BinaryOperator>(left, op, right);
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::parseStatement() {
    // A statement can be an expression or a declaration
    if (match(TokenType::Keyword)) {
        return parseDeclaration();
    }
    return parseExpression(); // Could be an expression statement
}

std::unique_ptr<ASTNode> Parser::parseDeclaration() {
    // Basic declaration handling (simplified)
    expect(TokenType::Keyword); // expect type keyword (int, float, etc.)
    auto type = currentToken(); // Get the type
    consume(); // Consume the type token
    expect(TokenType::Identifier); // Expect identifier for the variable name
    auto varName = currentToken();
    consume(); // Consume the identifier token
    return std::make_unique<VariableDeclaration>(varName, type);
}

std::unique_ptr<ASTNode> Parser::parseFunction() {
    // Simplified function parsing (to be expanded)
    expect(TokenType::Keyword); // expect function keyword (e.g., "int", "void")
    auto returnType = currentToken();
    consume();
    expect(TokenType::Identifier); // expect function name
    auto functionName = currentToken();
    consume();
    // Handle parameters and return an AST node
    return std::make_unique<FunctionDeclaration>(functionName, returnType);
}

} // namespace parser
} // namespace frontend
} // namespace zencc
