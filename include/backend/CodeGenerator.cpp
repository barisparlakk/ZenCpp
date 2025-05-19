#include "CodeGenerator.h"
#include <sstream>

namespace zencc {
namespace backend {
namespace codegen {

using namespace zencc::midend::ir;

std::vector<std::string> CodeGenerator::generate(const IR& ir) {
    std::vector<std::string> assembly;

    for (const auto& instr : ir.getInstructions()) {
        std::ostringstream line;

        switch (instr.op) {
            case OpCode::LoadConst:
                // Example: mov rax, 5
                line << "mov " << instr.dest << ", " << instr.arg1;
                break;
            case OpCode::Add:
                // mov rax, arg1
                // add rax, arg2
                assembly.push_back("mov rax, " + instr.arg1);
                assembly.push_back("add rax, " + instr.arg2);
                line << "mov " << instr.dest << ", rax";
                break;
            case OpCode::Label:
                line << instr.label + ":";
                break;
            case OpCode::Goto:
                line << "jmp " + instr.label;
                break;
            case OpCode::IfGoto:
                line << "cmp " + instr.arg1 + ", 0\njne " + instr.label;
                break;
            default:
                line << "; unhandled IR op";
                break;
        }

        if (!line.str().empty())
            assembly.push_back(line.str());
    }

    return assembly;
}

} // namespace codegen
} // namespace backend
} // namespace zencc
