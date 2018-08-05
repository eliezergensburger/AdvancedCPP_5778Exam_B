#include <iostream>
using namespace std;

class MyClass
{
public:
	MyClass() {}
	MyClass(const MyClass &myclass) { cout << "*"; }
	MyClass& operator= (const MyClass &myclass) { cout << "#"; return *this; }
};

int main()
{
	MyClass var1, var2;
	MyClass var3 = var1 = var2;
	MyClass var4(var3 = var2 = var1);
	cout << endl;
	system("pause");
	return 0;
}