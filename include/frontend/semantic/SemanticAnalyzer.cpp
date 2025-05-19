#include "SemanticAnalyzer.h"
#include <stdexcept>
#include <iostream>

namespace zencc {
namespace frontend {
namespace semantic {

SemanticAnalyzer::SemanticAnalyzer() {}

void SemanticAnalyzer::analyze(std::unique_ptr<ASTNode>& root) {
    // Starting with a simple type check, name resolution, and scope checks
    checkTypes(root.get());
    resolveNames(root.get());
    checkScope(root.get());
}

void SemanticAnalyzer::checkTypes(ASTNode* node) {
    // Basic type check example
    if (auto* varDecl = dynamic_cast<VariableDeclaration*>(node)) {
        if (varDecl->getType() == "int" && varDecl->getName().empty()) {
            throw std::runtime_error("Variable declared without a name");
        }
    }
}

void SemanticAnalyzer::resolveNames(ASTNode* node) {
    // Resolve the names for variable/function declarations (simplified)
    if (auto* varDecl = dynamic_cast<VariableDeclaration*>(node)) {
        symbolTable.addSymbol(varDecl->getName(), varDecl->getType());
    }
}

void SemanticAnalyzer::checkScope(ASTNode* node) {
    // Simple scope check (to be expanded)
    if (auto* varDecl = dynamic_cast<VariableDeclaration*>(node)) {
        // Check if the variable already exists in the current scope (simplified)
        if (symbolTable.symbolExists(varDecl->getName())) {
            throw std::runtime_error("Variable " + varDecl->getName() + " already declared in this scope.");
        }
    }
}

} // namespace semantic
} // namespace frontend
} // namespace zencc
