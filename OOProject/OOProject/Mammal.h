#pragma once
#include "Animal.h"
class Mammal: public Animal
{
public:
	Mammal(double, double, int);
	Mammal(double, double);
	Mammal(Mammal&);
	Mammal();
	virtual ~Mammal();
	void move(CPoint);
	virtual char* speak() = 0;
};

