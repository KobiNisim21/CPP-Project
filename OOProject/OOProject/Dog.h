#pragma once
#include "Mammal.h"
class Dog : public Mammal
{
	DECLARE_SERIAL(Dog);
public:
	Dog(double, double);
	Dog();
	virtual ~Dog();
	char* speak();
	void Serialize(CArchive& ar);
};
