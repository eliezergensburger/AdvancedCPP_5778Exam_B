#include <iostream>
#include <queue>
#include <string>

using namespace std;

template< class T >
void splitQ(queue<T> &source, queue<T> &q1, queue<T> &q2)
{
	while (!source.empty())
	{
		q1.push(source.front());
		source.pop();
		if (!source.empty())
		{
			q2.push(source.front());
			source.pop();
		}
	}
}

template< class T>
ostream& operator << (ostream& out, const queue<T> &q)
{
	queue<T> temp = q;
	while (!temp.empty()) 
	{ 
		out << temp.front(); 
		temp.pop();
		if (!temp.empty())
		{
			out << ' ';
		}
	}
	return out;
}

int main()
{
	int v[] = { 1,2,3,4,5,6,7,8,9,10 };

	queue<int> q, q1, q2;
	for (auto val : v) { q.push(val); }

	cout << "before split q:   " << q << endl;
	cout << "------------------------------------" << endl;

	cout << "splitting q" << endl;
	splitQ(q, q1, q2);
	cout << "------------------------------------" << endl;

	if (!q.empty()) { cout << "Error, q not empty  :" << q << endl; }

	if (!q1.empty())
	{
		cout << "after split q1:    " << q1 << endl;
	}
	else { cout << "q1 empty" << endl; }
	cout << "------------------------------------" << endl;

	if (!q2.empty())
	{
		cout << "after split q2:    " << q2 << endl;
	}
	else { cout << "q2 empty" << endl; }
	cout << "------------------------------------" << endl;

	queue<string> qs, qs1, qs2;

	qs.push("elaka"); qs.push("moed"); qs.push("demeir"); 
	qs.push("bet"); qs.push("aneyna");
	
	splitQ(qs, qs1, qs2);
	cout << "after split qs1:    " << qs1 << endl;
	cout << "after split qs2:    " << qs2 << endl;

	cout << "----------------- the END -------------------" << endl;

	system("Pause");
	return 0;
}
/**********************************************
before split q:   1 2 3 4 5 6 7 8 9 10
------------------------------------
splitting q
------------------------------------
after split q1:    1 3 5 7 9
------------------------------------
after split q2:    2 4 6 8 10
------------------------------------
after split qs1:    elaka demeir aneyna
after split qs2:    moed bet
----------------- the END -------------------
Press any key to continue . . .

***********************************************/

