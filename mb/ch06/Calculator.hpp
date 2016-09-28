#pragma once

class TokenStream;

void clean(TokenStream&);

class Calculator
{
public:
    Calculator(TokenStream&);

    double expression();
    double term();
    double primary();

private:
    TokenStream& tokenStream;

    double calculteValue(const double& value);
};

