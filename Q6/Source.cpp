#include <iostream>
#include <list>
using namespace std;

bool single_digit(int x) { return (x /10 == 0 ); }

class isOdd
{
public:
	bool operator()(int x) { return (x % 2) == 1; }
};

int main()
{
	int myints[] = { 15,36,-7,17,22,39,4,1,44 };

	list<int> mylist(myints, myints + 9);
	for (auto a : mylist) { cout << a << '\t'; }; cout << endl;

	mylist.remove_if(single_digit);
	for (auto a : mylist) { cout << a << '\t'; }; cout << endl;

	mylist.remove_if(isOdd());
	for (auto a : mylist) { cout << a << '\t'; }; cout << endl;

	int multiple = 4;
	auto mylambda = [multiple](int x) {return (x % multiple) == 0; };

	mylist.remove_if(mylambda);
	for (auto a : mylist) { cout << a << '\t'; }; cout << endl;

	cout << "mylist contains:" ;
	for (list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
	{
		cout << ' ' << *it;
	}
	cout << endl;

	system("pause");
	return 0;
}
