#ifndef ZENCC_SEMANTICANALYZER_H
#define ZENCC_SEMANTICANALYZER_H

#include <memory>
#include "ASTNode.h"
#include "SymbolTable.h"

namespace zencc {
namespace frontend {
namespace semantic {

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    void analyze(std::unique_ptr<ASTNode>& root);

private:
    void checkTypes(ASTNode* node);
    void resolveNames(ASTNode* node);
    void checkScope(ASTNode* node);

    SymbolTable symbolTable;
};

} // namespace semantic
} // namespace frontend
} // namespace zencc

#endif // ZENCC_SEMANTICANALYZER_H
