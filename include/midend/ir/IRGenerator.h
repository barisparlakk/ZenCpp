#ifndef ZENCC_IRGENERATOR_H
#define ZENCC_IRGENERATOR_H

#include "IR.h"
#include "ASTNode.h"

namespace zencc {
namespace midend {
namespace ir {

class IRGenerator {
public:
    IRGenerator();
    std::unique_ptr<IR> generate(const ASTNode* root);

private:
    int tempVarCount = 0;
    std::string newTemp();

    void generateNode(const ASTNode* node, IR& ir);
};

} // namespace ir
} // namespace midend
} // namespace zencc

#endif // ZENCC_IRGENERATOR_H
