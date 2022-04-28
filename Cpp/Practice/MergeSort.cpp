#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <cmath>

using namespace std;

typedef vector<int> Array;
void GetArray(Array &x)
{
    string cell, input;
    cout << " Please enter first array .." << endl;
    cin >> input;

    stringstream s(input);
    while (getline(s, cell, ','))
    {
        if (!regex_match(cell, regex("[+-]?[0-9]+")))
            cerr << "Invalid entry. Please enter valid number..." << endl;

        x.push_back(stoi(cell));
    }
}

void Merge(Array &A, int m, int p, int n)
{
    Array C;
    for (int i = m; i < n; i++)
    {
        if (A[m] < A[p + 1])
        {
            C[i] = A[m];
            m++;
        }
        else
        {
            C[i] = A[p + 1];
            p++;
        }
    }
    A = C;
}
void MergeSort(Array &A, int i, int j)
{
    if (i < j)
    {
        int p = round(i + j + 1) / 2;
        MergeSort(A, i, p);
        MergeSort(A, (p + 1), j);

        Merge(A, i, p, j);
    }
}
int main()
{
    try
    {
        Array A;
        GetArray(A);
        for (const auto& value : A)
        {
            cout << value << " ";
        }
        MergeSort(A, 0, A.size());

        for (const auto &value : A)
        {
            cout << value << " ";
        } 
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
