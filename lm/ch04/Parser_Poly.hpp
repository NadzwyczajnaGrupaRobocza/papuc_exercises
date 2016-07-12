#pragma once

#include <memory>
#include <ostream>
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
    Parser_Poly(const std::string&);
    ~Parser_Poly();
    std::unique_ptr<AST_Poly::Poly> parse();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

namespace AST_Poly
{
class Number;
class Mono;
class Poly;
class Coeff;
class CoeffIdx;

class AstVisitor
{
public:
    virtual ~AstVisitor() = default;
    virtual void visit(const Number&) = 0;
    virtual void visit(const Mono&) = 0;
    virtual void visit(const Poly&) = 0;
    virtual void visit(const Coeff&) = 0;
    virtual void visit(const CoeffIdx&) = 0;
};

class Node
{
public:
    virtual void accept(AstVisitor&) const = 0;
};

class Number : public Node
{
public:
    Number(int valueInit) : value{valueInit}
    {
    }

    void accept(AstVisitor& v) const override
    {
        v.visit(*this);
    }

    int getValue() const
    {
        return value;
    }

private:
    int value;
};

class Coeff : public Node
{
public:
    Coeff(std::unique_ptr<Number> valueInit) : value{std::move(valueInit)}
    {
    }
    void accept(AstVisitor& v) const override
    {
        v.visit(*this);
    }

    const Number& getValue() const
    {
        return *value;
    }

private:
    std::unique_ptr<Number> value;
};

class CoeffIdx : public Node
{
public:
    CoeffIdx(std::unique_ptr<Number> valueInit) : value(std::move(valueInit))
    {
    }

    void accept(AstVisitor& v) const override
    {
        v.visit(*this);
    }

    const Number& getValue() const
    {
        return *value;
    }

private:
    std::unique_ptr<Number> value;
};

class Mono : public Node
{
public:
    Mono(std::unique_ptr<Coeff> coeffInit,
         std::unique_ptr<CoeffIdx> coeffIdxInit)
        : coeff{std::move(coeffInit)}, coeffIdx{std::move(coeffIdxInit)}
    {
    }
    void accept(AstVisitor& v) const override
    {
        v.visit(*this);
    }

    const Node& getCoeff() const
    {
        return *coeff;
    }

    const Node& getCoeffIdx() const
    {
        return *coeffIdx;
    }

private:
    std::unique_ptr<Coeff> coeff;
    std::unique_ptr<CoeffIdx> coeffIdx;
};

class Poly : public Node
{
public:
    Poly(std::unique_ptr<Mono> headInit, std::unique_ptr<Poly> tailInit)
        : head{std::move(headInit)}, tail{std::move(tailInit)}
    {
    }

    void accept(AstVisitor& v) const override
    {
        v.visit(*this);
    }

    const Mono& getHead() const
    {
        return *head;
    }

    const Poly* getTailPtr() const
    {
        return tail.get();
    }

private:
    std::unique_ptr<Mono> head;
    std::unique_ptr<Poly> tail;
};

class AstPrintingVisitor : public AstVisitor
{
public:
    AstPrintingVisitor(std::ostream& outInit) : out{outInit}
    {
    }

    void visit(const Poly& p) override
    {
        out << "visiting poly\n";
        p.getHead().accept(*this);
        auto tailPtr = p.getTailPtr();
        if (tailPtr != nullptr)
        {
            tailPtr->accept(*this);
        }
        else
        {
            out << "END OF POLY\n";
        }
    }

    void visit(const Mono& m) override
    {
        out << "visiting mono\n";
        m.getCoeff().accept(*this);
        m.getCoeffIdx().accept(*this);
    }

    void visit(const Coeff& c) override
    {
        out << "visiting coeff\n";
        c.getValue().accept(*this);
    }

    void visit(const CoeffIdx& c) override
    {
        out << "visiting coeffIdx\n";
        c.getValue().accept(*this);
    }

    void visit(const Number& n) override
    {
        out << "number has value: " << n.getValue() << "\n";
    }

private:
    std::ostream& out;
};
}
