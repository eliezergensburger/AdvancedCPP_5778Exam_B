#include <iostream>
using namespace std;

class Person
{
	static int serial;
	int nb;
public:
	Person()  {	nb = ++serial;	}
	~Person() { cout << "bye " << nb << endl; }
};

int Person::serial = 0;

int main()
{
	{
		Person a;
		Person b;
		Person c;
	}
	system("pause");
	return 0;
}