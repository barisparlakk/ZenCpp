#include "IR.h"
#include <iostream>

namespace zencc {
namespace midend {
namespace ir {

void IR::addInstruction(const IRInstruction& instr) {
    instructions.push_back(instr);
}

void IR::dump() const {
    for (const auto& instr : instructions) {
        std::cout << instr.toString() << std::endl;
    }
}

std::string IRInstruction::toString() const {
    switch (op) {
        case OpCode::Add: return dest + " = " + arg1 + " + " + arg2;
        case OpCode::Sub: return dest + " = " + arg1 + " - " + arg2;
        case OpCode::Mul: return dest + " = " + arg1 + " * " + arg2;
        case OpCode::Div: return dest + " = " + arg1 + " / " + arg2;
        case OpCode::LoadConst: return dest + " = " + arg1;
        case OpCode::LoadVar: return dest + " = " + arg1;
        case OpCode::StoreVar: return arg1 + " = " + dest;
        case OpCode::Goto: return "goto " + label;
        case OpCode::IfGoto: return "if " + arg1 + " goto " + label;
        case OpCode::Label: return label + ":";
        case OpCode::Call: return dest + " = call " + arg1;
        case OpCode::Return: return "return " + arg1;
        default: return "unknown";
    }
}

} // namespace ir
} // namespace midend
} // namespace zencc
