#include "pch.h"
#include "Dog.h"
#include "Mammal.h"
#include "OOProject.h"
#include <afxwin.h>
#include "OOProjectDlg.h"

Dog::Dog(double x, double y) : Mammal(x, y, IDB_BITMAP_SMALL_DOG) {}

Dog::Dog() : Mammal() {}

Dog::~Dog() {}

char* Dog::speak()
{
	char* s = "Whoof! Whoof!";
	return s;
}

IMPLEMENT_SERIAL(Dog, CObject, 1)
void Dog::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	Animal::storeAnimal(ar, DOG);
}

