#include "pch.h"
#include "Mammal.h"
#include <math.h>

Mammal::Mammal(double x, double y, int c) : Animal(x, y, c) {}

Mammal::Mammal(double x, double y) : Animal(x, y) {}

Mammal::Mammal(Mammal& m) : Animal(m) {}

Mammal::Mammal() : Animal() {}

Mammal::~Mammal() {}

void Mammal::move(CPoint dest)
{
	this->setPlace(dest.x, dest.y);
}