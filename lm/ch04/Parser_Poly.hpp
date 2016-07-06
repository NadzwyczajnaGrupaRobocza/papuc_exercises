#pragma once

#include <memory>
#include <ostream>
#include <string>

namespace AST_Poly
{
class Node;
class Poly;
}

class Parser_Poly
{
public:
    Parser_Poly(const std::string &);
    ~Parser_Poly();
    std::unique_ptr<AST_Poly::Poly> parse();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

namespace AST_Poly
{
class Node
{
};

class Mono : public Node
{
};

class Poly : public Node
{
public:
    Poly(std::unique_ptr<Mono> headInit, std::unique_ptr<Poly> tailInit)
        : head{std::move(headInit)}, tail{std::move(tailInit)}
    {
    }

private:
    std::unique_ptr<Mono> head;
    std::unique_ptr<Poly> tail;
};
}
