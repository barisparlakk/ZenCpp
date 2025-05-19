#ifndef ZENCC_COMPILERDRIVER_H
#define ZENCC_COMPILERDRIVER_H

#include <string>

namespace zencc {
namespace driver {

class CompilerDriver {
public:
    bool compile(const std::string& inputPath, const std::string& outputExecutable);
};

} // namespace driver
} // namespace zencc

#endif // ZENCC_COMPILERDRIVER_H
