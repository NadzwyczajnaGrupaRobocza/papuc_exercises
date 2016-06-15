#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::sort;

void collectData(vector<double>&);
void printVector(const vector<double>&);
void showMediana(const vector<double>&);

int main()
{
    cout << "=== Program liczący medianę ===" << endl;
    cout << "= wpisanie wartości innej niż double kończy zbieranie danych" << endl;
    vector<double> temperatures;

    collectData(temperatures);
//    printVector(temperatures);
    sort(temperatures.begin(), temperatures.end());
    printVector(temperatures);
    showMediana(temperatures);

    return 0;
}

void collectData(vector<double>& dataContainer)
{
    double singleData;
    cout << "Podaj temperaturę: ";
    while(cin >> singleData)
    {
        dataContainer.push_back(singleData);
        cout << "Podaj temperaturę: ";
    }
}

void printVector(const vector<double>& vect)
{
    cout << "[ ";
    for(int i=0; i<vect.size(); ++i)
    {
        cout << vect[i];
        if(i!=vect.size()-1)
        {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}

void showMediana(const vector<double>& data)
{
    int numberOfData = data.size();
    if(numberOfData==0)
    {
        cout << "Brak danych => Brak mediany" << endl;
    }
    else if(numberOfData%2)
    {
        cout << "Mediana : " << data[data.size()/2] << endl;
    }
    else
    {
        cout << "Mediana : " << (data[data.size()/2 - 1] + data[data.size()/2]) / 2 << endl;
    }
}
