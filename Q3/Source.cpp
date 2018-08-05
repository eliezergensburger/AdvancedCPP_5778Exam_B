#include <iostream>
#include <cstring>
using namespace std;

class ClassOne
{
	const char* name;
public:
	ClassOne(const char* _name) :name(_strdup(_name))	{}
	virtual ~ClassOne() { cout << "ClassOne::~ClassOne\n"; delete[]name; }
};

class ClassTwo: public ClassOne
{
	const char* hobby;
public:
	ClassTwo(const char* _name,const char* _hobby) 
		:ClassOne(_name),hobby(_strdup(_hobby)) {}
	~ClassTwo() { cout << "ClassTwo::~ClassTwo\n"; delete[]hobby; }
};

int main()
{
	ClassOne* f = new ClassTwo("moed bet", "C++");
	delete f;
	system("pause");
	return 0;
}
