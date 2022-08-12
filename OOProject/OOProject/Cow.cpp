#include "pch.h"
#include "Cow.h"
#include "Mammal.h"
#include <afxwin.h>
#include "OOProject.h"
#include "OOProjectDlg.h"


Cow::Cow(double x, double y) : Mammal(x, y, IDB_BITMAP_SMALL_COW) {}

Cow::Cow() : Mammal() {}

Cow::~Cow() {}

char* Cow::speak()
{
	char* s = "Moooo!! Moooo!!";
	return s;
}

IMPLEMENT_SERIAL(Cow, CObject, 1)
void Cow::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	Animal::storeAnimal(ar, COW);
}
