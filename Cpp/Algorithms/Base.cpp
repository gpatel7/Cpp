#include <string>
#include <iostream>
using namespace std;

class B {

public:

B()
{
	cout << "B Constructor" << endl;
}

B(const B& b)
{
	cout << " B Copy Constructor" << endl;
}

~B()
{
	cout << "B Destructor" << endl;
}

protected:
	double price;
};

class D : public B
{
public:

D()
{
	cout<< "D Constructor" << endl;
}

D(const D& d)
{
        cout << " D Copy Constructor" << endl;
}

~D()    
{       
        cout << "D Destructor" << endl;
}

void memfun(const D& d, const B& b)
{
	double ret=this->price; //ok; used as this->price. Price is a protected member of base
	ret=d.price; //ok; uses price from derived object
	ret=b.price; //error; no access to price from
}

};

int main()
{
	B b=D();
	D d =D();
	d.memfun(d,b);
	return 1;
}
