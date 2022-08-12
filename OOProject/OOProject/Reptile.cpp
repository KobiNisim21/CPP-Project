#include "pch.h"
#include "Reptile.h"

Reptile::Reptile(double x, double y, int c) : Animal(x, y, c) {}

Reptile::Reptile(double x, double y) : Animal(x, y) {}

Reptile::Reptile(Reptile& m) : Animal(m) {}

Reptile::Reptile() : Animal() {}

Reptile::~Reptile() {}

void Reptile::move(CPoint dest)
{
	this->setPlace(dest.x, dest.y);
}

char* Reptile::speak()
{
	char* s = "Sorry! Can't speak...";
	return s;
}
