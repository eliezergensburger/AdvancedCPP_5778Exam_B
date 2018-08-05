#pragma once
#include "GENRE.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

class MovieMaker
{
protected:
	char* name;
	int numOfmovies;
	double salary;

public:
	virtual void setSalary(double sal) {};//cannot =0 if using in constructor
	virtual void add(Movie movie) = 0;
	virtual void remove(Movie movie) = 0;
	virtual void job() const = 0;
	string getName() const { return string(name); }
	int getNumOfMovies() const { return numOfmovies; }
	double getSalary() const { return salary; }

	void printDetails() const 
	{

		cout << "Name: " << getName() << endl;
		cout << "Num of Movies: " << getNumOfMovies() << endl;
		cout << "Salary:  " << fixed << setprecision(2) << getSalary() << endl;
		this->job();
	}
	void setName(const char* name)
	{
		if (name)
		{
			this->name = _strdup(name);
		}
		else throw "null name";
	}

	void setNumOfMovies(int n) 
	{
		if (n > 0)
		{
			numOfmovies = n;
		}
		else
		{
			throw "numof movies should be > 0";
		}
	}
	MovieMaker(const char* name, int num, double sal)
	{
		try
		{
			setName(name);
			setNumOfMovies(num);
			setSalary(sal);
		}
		catch (const char* msg)
		{
			throw(msg);
		}
	}

//	MovieMaker() {}
	virtual ~MovieMaker() {}

};
