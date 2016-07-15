#pragma once
#include <cmath>
#include <vector>
#include <exception>

class Polynomial
{
public:
    using CoeffContainer = std::vector<double>;
    using value_type = CoeffContainer::value_type;
    using size_type = CoeffContainer::size_type;

    Polynomial(const CoeffContainer& coeffsInit) : coeffs{coeffsInit}
    {
    }

    Polynomial(CoeffContainer&& coeffsInit) : coeffs{std::move(coeffsInit)}
    {
    }

    value_type operator[](size_type i) const
    {
        return coeffs.at(i);
    }

    size_type deg() const
    {
        return coeffs.size() - 1;
    }

    static constexpr auto epsilon = 0.000001;

private:
    CoeffContainer coeffs;
};

class Equation
{
public:
    using SolutionsContainer = std::set<Polynomial::value_type>;

    Equation(const Polynomial& polynomialInit) : p{polynomialInit}
    {
        if (p.deg() >= 3u)
            throw std::logic_error("Can't touch this!");
    }

    SolutionsContainer solve()
    {
        switch (p.deg())
        {
        case 0: return {};
        case 1: return solveLinear();
        case 2: return solveQuadratic();
        case 3: return solveCubic();
        default: throw std::logic_error("Can't touch this!");
        }
    }

private:
    SolutionsContainer solveLinear()
    {
        return {-1.0 * p[0] / p[1]};
    }

    SolutionsContainer solveQuadratic()
    {
        auto delta = p[1] * p[1] - 4.0 * p[0] * p[2];

        if (std::fabs(delta) < Polynomial::epsilon)
        {
            return {-1.0 * p[1] / (2.0 * p[2])};
        }
        else
        {
            if (delta > Polynomial::epsilon)
            {
                return {(-1.0 * p[1] - std::sqrt(delta)) / (2.0 * p[2]),
                        (-1.0 * p[1] + std::sqrt(delta)) / (2.0 * p[2])};
            }
            else
            {
                return {};
            }
        }
    }

    SolutionsContainer solveCubic()
    {
        auto R = (9.0 * p[3] * p[2] * p[1] - 27.0 * p[3] * p[3] * p[0]
                  - 2.0 * p[2] * p[2] * p[2]) / (54.0 * p[3] * p[3] * p[3]);

        auto Q = (3 * p[3] * p[1] - p[2] * p[2]) / (9.0 * p[3] * p[3]);

        auto D = Q * Q * Q + R * R;
        
        return {};
    }

    const Polynomial& p;
};
