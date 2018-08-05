#pragma once
#include "GENRE.h"
#include "Movie.h"
#include "MovieMaker.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

class Actor : public MovieMaker
{
	int numOfFans;
	vector<Movie> movies;
public:
	void setnumsOfFans(int fans){}
	Actor(const char* name, int numOfmovies, double sal, int fans)
		: MovieMaker(name, numOfmovies, sal)
	{
		setSalary(sal);
		setFans(fans);
	}

	void setFans(int fans)
	{
		if (fans >= 0)
		{
			numOfFans = fans;
		}
		else
		{
			throw "no negative fans";
		}
	}
	int getFans() const { return numOfFans; }
	void  printFans() const { cout << "num of fans : " << getFans() << endl; }
	virtual void setSalary(double sal)
	{
		if (sal < 0)
		{
			throw "no negative salary for MovieMaker";
		}
		else if (sal < 1000000 || sal > 20000000)
		{
			throw "salary out of range for Actor";
		}
		else
		{
				salary = sal;
		}	
	}
	void job() const
	{ 
		cout << "actor" << endl;
		printFans();
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
