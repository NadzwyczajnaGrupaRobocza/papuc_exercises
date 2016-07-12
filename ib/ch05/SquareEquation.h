#include <vector>

class Polynomial
{
	public:
	Polynomial(std::vector<double>);
	Polynomial();
	int getDegree()const;
	
double& operator[](int i)
	{
	return polynom[i];	
	}

	private:
	std::vector<double> polynom;
};

class SquareEquation
{
	public:
	SquareEquation(const Polynomial &sqr);
	std::vector<double> solveEquation();		
		
	private:
	double delta();
	bool isSquare();
	Polynomial square;

};
