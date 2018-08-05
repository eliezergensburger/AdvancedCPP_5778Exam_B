#pragma once
#include "GENRE.h"
#include <iostream>
#include <string>
using namespace std;

class Movie
{
	string name;
	GENRE type;
public:
	string getName() const { return name; }
	GENRE getType() const { return type; }

	void setName(string name) { name = name; }
	void setType(GENRE type) { type = type; }

	Movie() :name("noname"),type(UNDEFINED){};

	Movie(string name, GENRE type)
	{
		setName(name);
		setType(type);
	}
	virtual ~Movie() {};
};

