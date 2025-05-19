#ifndef ZENCC_PARSER_H
#define ZENCC_PARSER_H

#include <vector>
#include <memory>
#include "Token.h"
#include "ASTNode.h"

namespace zencc {
namespace frontend {
namespace parser {

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parse();

private:
    const std::vector<Token>& tokens;
    size_t currentPos;

    Token currentToken();
    Token consume();
    bool match(TokenType type);
    void expect(TokenType type);

    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseStatement();
    std::unique_ptr<ASTNode> parseDeclaration();
    std::unique_ptr<ASTNode> parseFunction();
};

} // namespace parser
} // namespace frontend
} // namespace zencc

#endif // ZENCC_PARSER_H
