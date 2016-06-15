#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Median
{
public:
    Median(const std::vector<T> &v)
        : values{v}
    {
    }

    T get()
    {
        if (values.size() == 0)
            return T{};

        auto middleIndex = values.size() / 2;

        std::nth_element(values.begin(), values.begin() + values.size()/2,
                         values.end());

        if (values.size() % 2 == 0)
        {
            return values[middleIndex - 1]/2 + values[middleIndex]/2;
        }
        else
        {
            return values[middleIndex];
        }
    }
private:
    std::vector<T> values;
};

int main()
{
    std::vector<double> temps;
    for (double temp ; std::cin >> temp; )
    {
        temps.push_back(temp);
    }

    std::cout << "Median: " << Median<double>(temps).get() << std::endl;
    return 0;
}
