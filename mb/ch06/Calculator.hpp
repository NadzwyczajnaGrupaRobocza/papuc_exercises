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
    constexpr static double epsilon{0.00001};

    double calculteValue(const double& value);
};

