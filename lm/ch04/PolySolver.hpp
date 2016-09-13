#pragma once
#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <numeric>
#include <set>
#include <stdexcept>
#include <vector>

class Polynomial
{
public:
    using value_type = double;
    using CoeffContainer = std::vector<value_type>;
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

    value_type operator()(value_type x) const
    {
        return std::accumulate(
            coeffs.rbegin(), coeffs.rend(), value_type{},
            [x](const value_type base, const value_type coeff) {
                return base * x + coeff;
            });
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
    using FloatingPt = Polynomial::value_type;
    using SolutionsContainer = std::set<FloatingPt>;

    Equation(const Polynomial& polynomialInit) : p{polynomialInit}
    {
        if (p.deg() > 3u)
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
        using namespace std::complex_literals;
        auto R_real = (9.0 * p[3] * p[2] * p[1] - 27.0 * p[3] * p[3] * p[0] -
                       2.0 * p[2] * p[2] * p[2]) /
                      (54.0 * p[3] * p[3] * p[3]);
        auto R = std::complex<FloatingPt>(R_real, 0.0);

        auto Q_real = (3 * p[3] * p[1] - p[2] * p[2]) / (9.0 * p[3] * p[3]);
        auto Q = std::complex<FloatingPt>(Q_real, 0.0);

        auto D = Q * Q * Q + R * R;

        auto S_3 = R + std::sqrt(D);
        auto T_3 = R - std::sqrt(D);
        auto S = std::pow(S_3, 1.0 / 3.0);
        auto T = std::pow(T_3, 1.0 / 3.0);

        auto b_over_3_a = std::complex<FloatingPt>{p[2] / (3.0 * p[3]), 0.0};
        auto fct = std::complex<FloatingPt>{0.0, std::sqrt(3.0) / 2.0};
        auto S_T_over_2 = (T + S) / 3.0;

        std::vector<std::complex<FloatingPt>> complexSolutions;
        complexSolutions.reserve(3);

        complexSolutions.push_back(S + T - b_over_3_a);
        complexSolutions.push_back(-1.0 * S_T_over_2 - b_over_3_a +
                                   fct * (S - T));
        complexSolutions.push_back(-1.0 * S_T_over_2 - b_over_3_a -
                                   fct * (S - T));

        SolutionsContainer solutions;

        // std::for_each(complexSolutions.begin(), complexSolutions.end(),
        //               [](const auto& c) { std::cout << "sol: " << c << "\n";
        //               });

        std::for_each(complexSolutions.begin(), complexSolutions.end(),
                      [&](const auto& cplxSol) {
                          if (std::fabs(cplxSol.imag()) < Polynomial::epsilon)
                          {
                              solutions.insert(cplxSol.real());
                          }
                      });

        return solutions;
    }

    const Polynomial& p;
};
