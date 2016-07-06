#include <vector>

class SquareEquation
{
	public:
	void setEquationEntries(float aA, float bB, float cC);
	std::vector<float> solveEquation();
	
	SquareEquation();
	SquareEquation(float, float, float);		
		
	private:
	float delta();
	bool isSquare();
	float a;
	float b;
	float c;

};
