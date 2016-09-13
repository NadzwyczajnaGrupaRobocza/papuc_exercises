#pragma once

#include <memory>
#include <string>

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
