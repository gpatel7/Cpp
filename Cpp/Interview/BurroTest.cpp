#include<iostream>

using namespace std;

class Child
{
    private:
    int i;
    public:
    void Print()
    {
        for(int x=0;x<=10;x++)
        {
            cout << "Printing X: " << x << endl;
        }
    }

};

int main()
{
    cout << "Testing my cpp skills " << endl;
}