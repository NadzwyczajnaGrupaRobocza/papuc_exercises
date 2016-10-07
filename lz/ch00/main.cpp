#include <boost/algorithm/algorithm.hpp>
#include <gsl/gsl>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

void fun(gsl::not_null<int*> i)
{
    using namespace std;
    cout << *i << endl;
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
