#ifndef ZENCC_ASSEMBLYEMITTER_H
#define ZENCC_ASSEMBLYEMITTER_H

#include <vector>
#include <string>

namespace zencc {
namespace backend {
namespace codegen {

class AssemblyEmitter {
public:
    void emit(const std::vector<std::string>& asmLines, const std::string& outFile);
};

} // namespace codegen
} // namespace backend
} // namespace zencc

#endif // ZENCC_ASSEMBLYEMITTER_H
