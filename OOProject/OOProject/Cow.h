#pragma once
#include "Mammal.h"
class Cow : public Mammal
{
DECLARE_SERIAL(Cow)
public:
	Cow(double, double);
	Cow();
	virtual ~Cow();
	char* speak();
	void Serialize(CArchive& ar);
};
