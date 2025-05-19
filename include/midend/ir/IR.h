#ifndef ZENCC_IR_H
#define ZENCC_IR_H

#include <string>
#include <vector>
#include <memory>

namespace zencc {
namespace midend {
namespace ir {

enum class OpCode {
    Add, Sub, Mul, Div,
    LoadConst, LoadVar, StoreVar,
    Goto, IfGoto,
    Label,
    Call, Return
};

struct IRInstruction {
    OpCode op;
    std::string dest;
    std::string arg1;
    std::string arg2;
    std::string label;  // For jump and label instructions

    std::string toString() const;
};

class IR {
public:
    void addInstruction(const IRInstruction& instr);
    void dump() const;

private:
    std::vector<IRInstruction> instructions;
};

} // namespace ir
} // namespace midend
} // namespace zencc

#endif // ZENCC_IR_H
