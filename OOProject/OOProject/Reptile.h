#pragma once
#include "Animal.h"
class Reptile : public Animal
{
public:
	Reptile(double, double, int);
	Reptile(double, double);
	Reptile(Reptile&);
	Reptile();
	virtual ~Reptile();
	void move(CPoint);
	char* speak();
};

