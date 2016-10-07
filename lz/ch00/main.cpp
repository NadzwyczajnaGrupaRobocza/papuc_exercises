#include <boost/algorithm/algorithm.hpp>
#include <gsl/gsl>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <chrono>

auto log()
{
    using namespace std::chrono_literals;
    auto i = 3h;
    std::cout << "time: " << i.count() << "h" << std::endl;
    return i;
}

void fun(gsl::not_null<int*> i)
{
    using namespace std::chrono_literals;
    using namespace std;
    cout << *i << endl;

    auto time = log();
    cout << ( time - 30min).count() << "min" << endl;
}

int main()
{
    char str1[] = "To be or not to be";
    char str2[40];

    /* copy to sized buffer (overflow safe): */
    strncpy(str2, str1, sizeof(str2));
#if _MSC_VER >= 1500

    using namespace std;
    cout << "hello papuc >" << endl;
#else

    using namespace std;
    cout << "hello papuc" << endl;
#endif

    int i = 34;
    fun(&i);
}
