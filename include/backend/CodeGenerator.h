#ifndef ZENCC_CODEGENERATOR_H
#define ZENCC_CODEGENERATOR_H

#include "../../midend/ir/IR.h"
#include <vector>
#include <string>

namespace zencc {
namespace backend {
namespace codegen {

class CodeGenerator {
public:
    std::vector<std::string> generate(const zencc::midend::ir::IR& ir);
};

} // namespace codegen
} // namespace backend
} // namespace zencc

#endif // ZENCC_CODEGENERATOR_H
