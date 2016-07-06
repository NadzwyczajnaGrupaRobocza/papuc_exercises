#pragma once

#include <string>
#include <memory>

class Parser
{
public:
    Parser(const std::string&);
    ~Parser();
    bool parse();
private:
    class Impl;
    std::unique_ptr<Impl> impl;
};
