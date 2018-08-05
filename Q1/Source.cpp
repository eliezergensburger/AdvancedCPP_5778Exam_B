#include <iostream>
using namespace std;

void P(int x) { cout << x; }

int main()
{
	P(0);
	auto f = [] { P(4); };
	auto g = [f] {P(2); f(); P(3); };
	P(9);
	g();
	system("pause");
}
// 09243
