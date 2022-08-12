#pragma once
#include "Reptile.h"
class Snake : public Reptile
{
DECLARE_SERIAL(Snake)
public:
	Snake(double, double);
	Snake(Snake&);
	Snake();
	virtual ~Snake();
	void Serialize(CArchive& ar);
};

