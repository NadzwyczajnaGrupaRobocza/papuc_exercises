#pragma once

#include <memory>
#include <ostream>
#include <string>

namespace AST
{
class Node;
}

class Parser_Ast
{
public:
    Parser_Ast(const std::string&);
    ~Parser_Ast();
    std::unique_ptr<AST::Node> parse();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

namespace AST
{
class Symbol;
class Number;
class Asignment;

class AstVisitor
{
public:
    virtual ~AstVisitor() = default;
    virtual void visit(Symbol&) = 0;
    virtual void visit(Number&) = 0;
    virtual void visit(Asignment&) = 0;
};

class Node
{
public:
    virtual ~Node() = default;
    virtual void accept(AstVisitor&) = 0;
};

class Terminal : public Node
{
};

class Number : public Terminal
{
public:
    Number(int valueInit) : value{valueInit}
    {
    }

    void accept(AstVisitor& v)
    {
        v.visit(*this);
    }

    int getValue()
    {
        return value;
    }

private:
    int value;
};

class Symbol : public Terminal
{
public:
    Symbol(const std::string& valueInit) : value{valueInit}
    {
    }

    void accept(AstVisitor& v)
    {
        v.visit(*this);
    }

    const std::string& getId()
    {
        return value;
    }

private:
    std::string value;
};

class Asignment : public Node
{
public:
    Asignment(std::unique_ptr<Symbol> lhsInit,
              std::unique_ptr<Terminal> rhsInit)
        : lhs{std::move(lhsInit)}, rhs{std::move(rhsInit)}
    {
    }

    void accept(AstVisitor& v)
    {
        v.visit(*this);
    }

    Symbol& getLhs()
    {
        return *lhs;
    }

    Terminal& getRhs()
    {
        return *rhs;
    }

private:
    std::unique_ptr<Symbol> lhs;
    std::unique_ptr<Terminal> rhs;
};

class AstPrintingVisitor : public AstVisitor
{
public:
    AstPrintingVisitor(std::ostream& outInitializer) : out{outInitializer}
    {
    }

    void visit(Symbol& sym) override
    {
        out << sym.getId();
    }

    void visit(Number& num) override
    {
        out << num.getValue();
    }

    void visit(Asignment& ass) override
    {
        ass.getLhs().accept(*this);
        out << " <- ";
        ass.getRhs().accept(*this);
    }

private:
    std::ostream& out;
};
}
