#pragma once
#include <afxwin.h>

class Animal : public CObject
{
private:
	double x;
	double y;
	int img;
	UUID id;
public:
	Animal(double, double, int);
	Animal(double, double);
	Animal();
	Animal(Animal&);
	virtual ~Animal();
	virtual void move(CPoint) = 0;
	double getX() const;
	double getY() const;
	void setX(const double);
	void setY(const double);
	void setPlace(const double, const double);
	int getImg() const;
	void setImg(int);
	void Draw(CDC*);
	bool isInside(CPoint);
	virtual char* speak() = 0;
	void storeAnimal(CArchive&, int);
};

