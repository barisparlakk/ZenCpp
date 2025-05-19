#include "IRGenerator.h"

namespace zencc {
namespace midend {
namespace ir {

IRGenerator::IRGenerator() {}

std::unique_ptr<IR> IRGenerator::generate(const ASTNode* root) {
    auto ir = std::make_unique<IR>();
    generateNode(root, *ir);
    return ir;
}

std::string IRGenerator::newTemp() {
    return "t" + std::to_string(tempVarCount++);
}

void IRGenerator::generateNode(const ASTNode* node, IR& ir) {
    // Very basic example: handle integer literals
    if (auto* lit = dynamic_cast<const IntegerLiteral*>(node)) {
        std::string temp = newTemp();
        ir.addInstruction({OpCode::LoadConst, temp, std::to_string(lit->getValue()), "", ""});
    }

    // You would recursively handle BinaryOp, Assignments, etc.
}

} // namespace ir
} // namespace midend
} // namespace zencc
