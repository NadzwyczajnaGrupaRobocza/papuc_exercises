#include "SquareEquation.h"

#include <iostream>

using namespace std;

int main()
{
try
{
SquareEquation eq(1,1,1);
cout<<eq.solveEquation()[0]<<endl;
cout<<eq.solveEquation()[1]<<endl;

return 0;
}
catch (exception& e)
{
cout<<e.what();
}

}
