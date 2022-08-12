#include "pch.h"
#include "Animal.h"
#include "OOProjectDlg.h"
#pragma comment(lib, "rpcrt4.lib")

Animal::Animal(double x, double y, int c)
{
	this->x = x;
	this->y = y;
	this->img = c;
	UuidCreate(&this->id);
}

Animal::Animal(double x, double y) 
{
	this->x = x;
	this->y = y;
	this->img = NULL;
	UuidCreate(&this->id);
}

Animal::Animal() 
{
	this->x = 0;
	this->y = 0;
	this->img = NULL;
	UuidCreate(&this->id);
}

Animal::Animal(Animal& a) 
{
	this->x = a.getX();
	this->y = a.getY();
	this->img = a.getImg();
	UuidCreate(&this->id);
}

Animal::~Animal() {}

double Animal::getX() const { return this->x; }

double Animal::getY() const { return this->y; }

void Animal::setX(const double x) { this->x = x; }

void Animal::setY(const double y) { this->y = y; }

void Animal::setPlace(const double x, const double y) 
{
	this->setX(x);
	this->setY(y);
}

int Animal::getImg() const { return this->img; }

void Animal::setImg(int c) { this->img = c; }

void Animal::Draw(CDC* dc)
{
	//dc->Rectangle(this->getX(), this->getY(), this->getX() + 10, this->getY() + 10);
	BITMAP bm;
	CBitmap hBitmap;
	hBitmap.LoadBitmapW(this->img);
	HBITMAP animBitmap = (HBITMAP)hBitmap.GetSafeHandle();

	GetObject(animBitmap, sizeof(bm), &bm);
	//CPoint size(bm.bmWidth, bm.bmHeight);
	//dc->DPtoLP(&size);

	CPoint org(0, 0);
	dc->DPtoLP(&org);

	CDC memDC;
	memDC.CreateCompatibleDC(dc);
	memDC.SetMapMode(dc->GetMapMode());

	HBITMAP hBmOld = (HBITMAP)SelectObject(memDC.m_hDC, animBitmap);

	//dc->BitBlt(this->getX(), this->getY(), size.x, size.y, &memDC, org.x, org.y, SRCCOPY);
	dc->BitBlt(this->getX(), this->getY(), bm.bmWidth, bm.bmHeight, &memDC, org.x, org.y, SRCCOPY);


	SelectObject(memDC.m_hDC, hBmOld);
}

bool Animal::isInside(CPoint clickedPoint) {
	// check is inside by the x,y of instance and the size of bitmap
	BITMAP bm;
	CBitmap hBitmap;
	hBitmap.LoadBitmapW(this->img);
	HBITMAP animBitmap = (HBITMAP)hBitmap.GetSafeHandle();
	GetObject(animBitmap, sizeof(bm), &bm);

	return (clickedPoint.x >= this->getX() && clickedPoint.x <= this->getX() + bm.bmWidth
		&& clickedPoint.y >= this->getY() && clickedPoint.y <= this->getY() + bm.bmHeight);
}

void Animal::storeAnimal(CArchive& ar, int animalIndex) {
	if (ar.IsStoring()) {
		ar << animalIndex << x << y << img;
	}
	else {
		ar >> x >> y >> img;
	}
}