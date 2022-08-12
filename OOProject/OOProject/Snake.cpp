#include "pch.h"
#include "Snake.h"
#include <afxwin.h>
#include "OOProject.h"
#include "OOProjectDlg.h"


Snake::Snake(double x, double y) : Reptile(x, y,IDB_BITMAP_SMALL_SNAKE) {}

Snake::Snake(Snake& s) : Reptile(s) {}

Snake::Snake() : Reptile() {}

Snake::~Snake() {}

IMPLEMENT_SERIAL(Snake, CObject, 1)
void Snake::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	Animal::storeAnimal(ar, SNAKE);
}