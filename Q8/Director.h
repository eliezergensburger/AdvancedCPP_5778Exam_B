#pragma once
#include "GENRE.h"
#include "Movie.h"
#include "MovieMaker.h"
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <algorithm>

class Director : public MovieMaker
{
	int sizeOfCrew;
	list<Movie> movies;
public:
	void setnumsOfFans(int fans) {}
	Director(const char* name, int numOfmovies, double sal, int crew)
		: MovieMaker(name, numOfmovies, sal)
	{
		setSalary(sal);
		setSizeOfCrew(crew);
	}

	void setSizeOfCrew(int crew)
	{
		if (crew >= 0)
		{
			sizeOfCrew = crew;
		}
		else
		{
			throw "no negative crew";
		}
	}
	int getSizeOfCrew() const { return sizeOfCrew; }
	void  printCrew() const { cout << "size of crew : " << getSizeOfCrew() << endl; }
	virtual void setSalary(double sal)
	{
		if (sal < 0)
		{
			throw "no negative salary for MovieMaker";
		}
		else if (sal < 1000000 || sal > 5000000)
		{
			throw "salary out of range for Director";
		}
		else
		{
			salary = sal;
		}
	}
	void job() const
	{
		cout << "director" << endl;
		printCrew();
	}
	virtual void add(Movie movie)
	{
		movies.push_back(movie);
		++numOfmovies;
	}
	virtual void remove(Movie movie)
	{
		string mname = movie.getName();
		remove_if(movies.begin(), movies.end(), [=](Movie m) {return mname == m.getName(); });
		--numOfmovies;
	}
};

