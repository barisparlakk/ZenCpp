#include "AssemblyEmitter.h"
#include <fstream>

namespace zencc {
namespace backend {
namespace codegen {

void AssemblyEmitter::emit(const std::vector<std::string>& asmLines, const std::string& outFile) {
    std::ofstream out(outFile);
    if (!out.is_open()) return;

    out << "section .text\n";
    out << "global _start\n\n";
    out << "_start:\n";

    for (const auto& line : asmLines) {
        out << "    " << line << "\n";
    }

    out << "    mov rax, 60\n";
    out << "    xor rdi, rdi\n";
    out << "    syscall\n"; // exit(0)
}

} // namespace codegen
} // namespace backend
} // namespace zencc
