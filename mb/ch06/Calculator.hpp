#pragma once

class ITokenStream;

void clean(ITokenStream&);

class Calculator
{
public:
    Calculator(ITokenStream&);

    double expression();
    double term();
    double primary();

private:
    ITokenStream& tokenStream;

    double calculteValue(const double& value);
};

