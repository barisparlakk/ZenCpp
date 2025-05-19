#include "frontend/lexer/Lexer.h"

using namespace zencc::frontend;

Lexer::Lexer(const std::string& source)
    : m_source(source), m_position(0), m_line(1), m_column(1) {}

Token Lexer::nextToken() {
    // Tokenization logic placeholder
    return Token(TokenType::EOF_TOKEN, "", m_line, m_column);
}


// src/frontend/parser/Parser.cpp
#include "frontend/parser/Parser.h"

using namespace zencc::frontend;

Parser::Parser(const std::vector<Token>& tokens)
    : m_tokens(tokens), m_current(0) {}

std::unique_ptr<Statement> Parser::parse() {
    // Parsing logic placeholder
    return nullptr;
}


// src/frontend/ast/Expression.cpp
#include "frontend/ast/Expression.h"

using namespace zencc::frontend;

Expression::~Expression() = default;


// src/frontend/ast/Statement.cpp
#include "frontend/ast/Statement.h"

using namespace zencc::frontend;

Statement::~Statement() = default;


// src/frontend/ast/PrintStatement.cpp
#include "frontend/ast/PrintStatement.h"

using namespace zencc::frontend;

PrintStatement::PrintStatement(std::unique_ptr<Expression> expression)
    : m_expression(std::move(expression)) {}

void PrintStatement::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}


// src/backend/CodeGenerator.cpp
#include "backend/CodeGenerator.h"
#include <iostream>

using namespace zencc::backend;

void CodeGenerator::generate(const Statement& stmt) {
    std::cout << "Generating code for statement" << std::endl;
    // Codegen logic placeholder
}


// src/driver/CompilerDriver.cpp
#include "frontend/lexer/Lexer.h"
#include "frontend/parser/Parser.h"
#include "backend/CodeGenerator.h"
#include <fstream>
#include <iostream>

using namespace zencc;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: zencc <source_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Failed to open source file." << std::endl;
        return 1;
    }

    std::string sourceCode((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    frontend::Lexer lexer(sourceCode);
    std::vector<frontend::Token> tokens;
    for (auto token = lexer.nextToken(); token.type != frontend::TokenType::EOF_TOKEN; token = lexer.nextToken()) {
        tokens.push_back(token);
    }

    frontend::Parser parser(tokens);
    auto ast = parser.parse();

    backend::CodeGenerator codegen;
    if (ast) {
        codegen.generate(*ast);
    }

    return 0;
}