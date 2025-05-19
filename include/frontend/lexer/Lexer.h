#include "Lexer.h"
#include <cctype>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

namespace zencc {
namespace frontend {
namespace lexer {

// Static map for C++ keywords (simplified for this example)
const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"int", TokenType::Keyword},
    {"float", TokenType::Keyword},
    {"if", TokenType::Keyword},
    {"else", TokenType::Keyword},
    {"return", TokenType::Keyword},
    // Add other keywords here...
};

Lexer::Lexer(const std::string& source)
    : source(source), currentPos(0), line(1), column(1) {}

Lexer::~Lexer() {}

std::vector<Token> Lexer::tokenize() {
    tokens.clear();
    while (currentPos < source.length()) {
        processNextToken();
    }
    tokens.push_back(Token(TokenType::EndOfFile, "", line, column));
    return tokens;
}

void Lexer::processNextToken() {
    char currentChar = source[currentPos];

    // Skip whitespace and handle new lines
    if (std::isspace(currentChar)) {
        if (currentChar == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        currentPos++;
        return;
    }

    // Process identifiers and keywords
    if (std::isalpha(currentChar) || currentChar == '_') {
        size_t start = currentPos;
        while (std::isalnum(source[currentPos]) || source[currentPos] == '_') {
            currentPos++;
        }
        std::string value = source.substr(start, currentPos - start);
        TokenType type = isKeyword(value) ? TokenType::Keyword : TokenType::Identifier;
        tokens.push_back(Token(type, value, line, column));
        column += value.length();
        return;
    }

    // Process numbers (literals)
    if (std::isdigit(currentChar)) {
        size_t start = currentPos;
        while (std::isdigit(source[currentPos])) {
            currentPos++;
        }
        std::string value = source.substr(start, currentPos - start);
        tokens.push_back(Token(TokenType::Literal, value, line, column));
        column += value.length();
        return;
    }

    // Process operators (simplified)
    if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
        std::string op(1, currentChar);
        tokens.push_back(Token(TokenType::Operator, op, line, column));
        currentPos++;
        column++;
        return;
    }

    // Process punctuation
    if (currentChar == ';' || currentChar == '{' || currentChar == '}' || currentChar == '(' || currentChar == ')') {
        std::string punct(1, currentChar);
        tokens.push_back(Token(TokenType::Punctuation, punct, line, column));
        currentPos++;
        column++;
        return;
    }

    // Process comments (single line for simplicity)
    if (currentChar == '/' && source[currentPos + 1] == '/') {
        size_t start = currentPos;
        while (currentPos < source.length() && source[currentPos] != '\n') {
            currentPos++;
        }
        std::string comment = source.substr(start, currentPos - start);
        tokens.push_back(Token(TokenType::Comment, comment, line, column));
        column += comment.length();
        return;
    }

    // Handle unknown characters
    tokens.push_back(Token(TokenType::Unknown, std::string(1, currentChar), line, column));
    currentPos++;
    column++;
}

bool Lexer::isKeyword(const std::string& str) const {
    return keywords.find(str) != keywords.end();
}

bool Lexer::isIdentifier(const std::string& str) const {
    return std::isalpha(str[0]) || str[0] == '_';
}

bool Lexer::isLiteral(const std::string& str) const {
    return std::isdigit(str[0]);
}

bool Lexer::isOperator(char ch) const {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool Lexer::isPunctuation(char ch) const {
    return ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')';
}

bool Lexer::isPreprocessorDirective(const std::string& str) const {
    return str[0] == '#'; // For simplicity, consider '#' as preprocessor directive
}

bool Lexer::isComment(const std::string& str) const {
    return str.substr(0, 2) == "//"; // Simplified for single-line comments
}

} // namespace lexer
} // namespace frontend
} // namespace zencc
