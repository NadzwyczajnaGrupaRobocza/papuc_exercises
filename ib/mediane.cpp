#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double mediane(vector<double> data)
{
int a = data.size();
const int zero = 0;

if(data.size() == 0)
{
cout<<"Error, no data probided!"<<endl;
}

else if(data.size() % 2 == 0)
{
return (data[data.size()/2-1] + data[data.size()/2])/2;
}
else
{
return data[data.size()/2];
}

}


int main()
{
double dat;
vector<double> data;

while(cin>>dat)
{
data.push_back(dat);
}

cout<<mediane(data);

return 0;

}
