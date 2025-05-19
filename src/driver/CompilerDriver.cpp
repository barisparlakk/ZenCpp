#include "CompilerDriver.h"
#include "../frontend/lexer/Lexer.h"
#include "../frontend/parser/Parser.h"
#include "../frontend/ast/AST.h"
#include "../midend/ir/IRGenerator.h"
#include "../backend/codegen/CodeGenerator.h"
#include "../backend/codegen/AssemblyEmitter.h"

#include <fstream>
#include <cstdlib> // system()

namespace zencc {
namespace driver {

bool CompilerDriver::compile(const std::string& inputPath, const std::string& outputExecutable) {
    using namespace zencc::frontend::lexer;
    using namespace zencc::frontend::parser;
    using namespace zencc::midend::ir;
    using namespace zencc::backend::codegen;

    // Read input source
    std::ifstream inFile(inputPath);
    if (!inFile) return false;

    std::string source((std::istreambuf_iterator<char>(inFile)),
                        std::istreambuf_iterator<char>());

    // 1. Lexing
    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // 2. Parsing
    Parser parser(tokens);
    auto ast = parser.parseProgram();

    // 3. IR Generation
    IRGenerator irGen;
    auto ir = irGen.generate(ast);

    // 4. Codegen
    CodeGenerator codegen;
    auto asmLines = codegen.generate(ir);

    // 5. Emit ASM
    std::string asmFile = "out.asm";
    AssemblyEmitter emitter;
    emitter.emit(asmLines, asmFile);

    // 6. NASM + LD/GCC
    std::string objFile = "out.o";
    std::string cmdAssemble = "nasm -f elf64 " + asmFile + " -o " + objFile;
    std::string cmdLink = "ld " + objFile + " -o " + outputExecutable;

    if (system(cmdAssemble.c_str()) != 0) return false;
    if (system(cmdLink.c_str()) != 0) return false;

    return true;
}

} // namespace driver
} // namespace zencc
