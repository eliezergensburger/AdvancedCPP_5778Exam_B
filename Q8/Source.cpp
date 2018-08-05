#include "GENRE.h"
#include "Movie.h"
#include "MovieMaker.h"
#include "Actor.h"
#include "Director.h"
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	try
	{
		list<MovieMaker*> crazies;
		crazies.push_back(new Actor("sacha baron cohen", 56, 15000000, 1000));
		crazies.push_back(new Director("shlomo Hamelech", 12, 5000000, 2000));
		for (auto it = crazies.begin(); it != crazies.end(); it++)
		{
			(*it)->printDetails();
			cout << endl;
		}

	}
	catch (const char * msg)
	{
		cout << msg << endl;
	}	
	system("pause");
	return 0;

}