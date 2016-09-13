#include <iostream>
#include "ch_04_05.hpp"



double calculator::compute(double arg1, double arg2)
{

switch(action)
{
case '+':
		
	return arg1 + arg2;
	break;
case '-':
	return arg1 - arg2;
	break;
case '*':
	return arg1 * arg2;
	break;
case ':':
	if(arg2 == 0)
	{
	cout<<"Bad arguments!!!!";
	break;	
	}
	else
	return arg1 / arg2;
	break;
}
}



