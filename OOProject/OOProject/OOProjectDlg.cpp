
// OOProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "OOProject.h"
#include "OOProjectDlg.h"
#include "afxdialogex.h"
#include "Dog.h"
#include "Cow.h"
#include "Snake.h"
#include <iostream>
#include <windows.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COOProjectDlg dialog


COOProjectDlg::COOProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OOPROJECT_DIALOG, pParent)
	, speakTextBox(_T(DEFAULT_SPEAK))
{
	currMovingAnimal = NULL;
	currDraggingAnimal = NULL;
	vecSize = 0;
	srand(time(0));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isInMovingProc = false;
	isPressed = false;
}

COOProjectDlg::~COOProjectDlg()
{
	for (vector<Animal*>::iterator it = animalsVec.begin(); it != animalsVec.end(); ++it)
	{
		delete *it;
	}
}

void COOProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DOG, dogButtonIcon);
	DDX_Control(pDX, IDC_COW, cowButtonIcon);
	DDX_Control(pDX, IDC_SNAKE, snakeButtonIcon);
	DDX_Control(pDX, ID_PLUS_DOG, plusDogButton);
	DDX_Control(pDX, IDC_PLUS_COW, plusCowButton);
	DDX_Control(pDX, IDC_PLUS_SNAKE, plusSnakeButton);
	DDX_Control(pDX, ID_MINUS_DOG, minusDogButton);
	DDX_Control(pDX, IDC_MINUS_COW, minusCowButton);
	DDX_Control(pDX, IDC_MINUS_SNAKE, minusSnakeButton);
	DDX_Control(pDX, IDC_BUTTON_UNDO, undoButton);
	DDX_Control(pDX, IDC_BUTTON_REDO, redoButton);
	DDX_Control(pDX, IDC_BUTTON_LOAD, loadButton);
	DDX_Control(pDX, IDC_BUTTON_SAVE, saveButton);
	DDX_Control(pDX, IDC_FARM, farmBox);
	DDX_Text(pDX, IDC_TEXTBOX, speakTextBox);
}

BEGIN_MESSAGE_MAP(COOProjectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_PLUS_DOG, &COOProjectDlg::OnBnClickedPlusDog)
	ON_BN_CLICKED(IDC_PLUS_COW, &COOProjectDlg::OnBnClickedPlusCow)
	ON_BN_CLICKED(IDC_PLUS_SNAKE, &COOProjectDlg::OnBnClickedPlusSnake)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_DOG, &COOProjectDlg::OnBnClickedDog)
	ON_BN_CLICKED(IDC_COW, &COOProjectDlg::OnBnClickedCow)
	ON_BN_CLICKED(IDC_SNAKE, &COOProjectDlg::OnBnClickedSnake)
	ON_BN_CLICKED(ID_MINUS_DOG, &COOProjectDlg::OnBnClickedMinusDog)
	ON_BN_CLICKED(IDC_MINUS_COW, &COOProjectDlg::OnBnClickedMinusCow)
	ON_BN_CLICKED(IDC_MINUS_SNAKE, &COOProjectDlg::OnBnClickedMinusSnake)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &COOProjectDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_REDO, &COOProjectDlg::OnBnClickedButtonRedo)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &COOProjectDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &COOProjectDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTONHELP, &COOProjectDlg::OnBnClickedButtonHELP)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// COOProjectDlg message handlers

BOOL COOProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MoveWindow(0, 0, 900, 650);

	dogButtonBitmap.LoadBitmapW(IDB_BITMAP_SMALL_DOG);
	HBITMAP dogBitmap = (HBITMAP)dogButtonBitmap.GetSafeHandle();
	dogButtonIcon.SetBitmap(dogBitmap);

	cowButtonBitmap.LoadBitmapW(IDB_BITMAP_SMALL_COW);
	HBITMAP cowBitmap = (HBITMAP)cowButtonBitmap.GetSafeHandle();
	cowButtonIcon.SetBitmap(cowBitmap);

	snakeButtonBitmap.LoadBitmapW(IDB_BITMAP_SMALL_SNAKE);
	HBITMAP snakeBitmap = (HBITMAP)snakeButtonBitmap.GetSafeHandle();
	snakeButtonIcon.SetBitmap(snakeBitmap);

	plusButtonBitmap.LoadBitmapW(IDB_BITMAP_PLUS);
	HBITMAP plusBitmap = (HBITMAP)plusButtonBitmap.GetSafeHandle();
	plusDogButton.SetBitmap(plusBitmap);

	plusCowButton.SetBitmap(plusBitmap);
	plusSnakeButton.SetBitmap(plusBitmap);

	minusButtonBitmap.LoadBitmapW(IDB_BITMAP_MINUS);
	HBITMAP minusBitmap = (HBITMAP)minusButtonBitmap.GetSafeHandle();
	minusDogButton.SetBitmap(minusBitmap);

	minusCowButton.SetBitmap(minusBitmap);
	minusSnakeButton.SetBitmap(minusBitmap);

	redoButtonBitmap.LoadBitmapW(IDB_BITMAP_REDO);
	HBITMAP redoBitmap = (HBITMAP)redoButtonBitmap.GetSafeHandle();
	redoButton.SetBitmap(redoBitmap);

	undoButtonBitmap.LoadBitmapW(IDB_BITMAP_UNDO);
	HBITMAP undoBitmap = (HBITMAP)undoButtonBitmap.GetSafeHandle();
	undoButton.SetBitmap(undoBitmap);

	loadButtonBitmap.LoadBitmapW(IDB_BITMAP_LOAD);
	HBITMAP loadBitmap = (HBITMAP)loadButtonBitmap.GetSafeHandle();
	loadButton.SetBitmap(loadBitmap);

	saveButtonBitmap.LoadBitmapW(IDB_BITMAP_SAVE);
	HBITMAP saveBitmap = (HBITMAP)saveButtonBitmap.GetSafeHandle();
	saveButton.SetBitmap(saveBitmap);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COOProjectDlg::OnPaint()
{
	CPaintDC dc(this);
	for (vector<Animal*>::iterator it = animalsVec.begin(); it != animalsVec.end(); ++it)
	{
		(*it)->Draw(&dc);
	}

	if (isInMovingProc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
		RECT rc;
		SetRect(&rc, currMovingAnimal->getX(), currMovingAnimal->getY(), currMovingAnimal->getX() + 60, currMovingAnimal->getY() + 50);
		FrameRect(dc, &rc, brush);
	}
	else if (currMovingAnimal)
	{
		HBRUSH brush = CreateSolidBrush(RGB(240, 240, 240));
		RECT rc;
		SetRect(&rc, currMovingAnimal->getX(), currMovingAnimal->getY(), currMovingAnimal->getX() + 60, currMovingAnimal->getY() + 50);
		FrameRect(dc, &rc, brush);
	}

	speakTextBox = DEFAULT_SPEAK;
	UpdateData(false);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COOProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Helper Functions
CPoint COOProjectDlg::GetRandomizedPosition()
{
	CPoint point;
	PointInBoundries(point);
	return point;
}

bool COOProjectDlg::PointInBoundries(CPoint& point)
{
	CPoint topLeft, bottomRight, h, w;
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_FARM);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	topLeft = rect.TopLeft();
	bottomRight = rect.BottomRight();
	h = rect.Height();
	w = rect.Width();

	if (point.x)
	{
		// Check if given point is in boundries
		return (point.x >= topLeft.x && point.x <= (w.x - 30) && point.y >= topLeft.y && point.y <= (h.x + 60));
	}
	else
	{
		// Given point has default values, create random values in farm boundries
		point.x = (rand() % (w.x - 60) + topLeft.x);
		point.y = (rand() % (h.x - 65) + topLeft.y + 15);
		return true;
	}	
}

template< typename T >
void COOProjectDlg::AddAnimal()
{
	CPoint point;
	point = this->GetRandomizedPosition();
	T* newAnim = new T(point.x, point.y);
	animalsVec.push_back(newAnim);
	vecSize++;
	Action play = { newAnim, CREATE, point.x, point.y };
	actionsMade.push_back(play);
	invalidateFarm();
}

template< typename T >
void COOProjectDlg::AddAnimal(Animal* a)
{
	T* newAnim = new T(a->getX(), a->getY());
	animalsVec.push_back(newAnim);
	vecSize++;
	invalidateFarm();
}

template< typename T >
void COOProjectDlg::DeleteAnimal(bool shouldAddAction)
{
	if (animalsVec.size() == 0)
	{
		MessageBox(_T("No animals in farm!"));
	}
	else
	{
		for (vector<Animal*>::reverse_iterator it = animalsVec.rbegin(); it != animalsVec.rend(); ++it)
		{
			if (dynamic_cast<T*>(*it))
			{
				Animal* animal(*it);
				animalsVec.erase(--(it.base()));
				vecSize--;
				invalidateFarm();
				if (shouldAddAction)
				{
					Action play = { animal, REMOVE, animal->getX(), animal->getY() };
					actionsMade.push_back(play);
				}
				return;
			}
		}
		MessageBox(_T("Cannot delete this animal!"));
	}
}

template< typename T >
void COOProjectDlg::MakeAnimalSpeak()
{
	T* animal = new T();
	speakTextBox = animal->speak();
	UpdateData(false);
}

// End of Helper Functions


// Add animals buttons
void COOProjectDlg::OnBnClickedPlusDog()
{
	// Clicked on add new dog
	AddAnimal<Dog>();
}

void COOProjectDlg::OnBnClickedPlusCow()
{
	//Clicked on new cow
	AddAnimal<Cow>();
}

void COOProjectDlg::OnBnClickedPlusSnake()
{
	//Clicked on new snake
	AddAnimal<Snake>();
}
// End of Add animals buttons


// Global mouse events handling
void COOProjectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (isInMovingProc)
	{
		if (PointInBoundries(point))
		{
			Action play = { currMovingAnimal, MOVE, currMovingAnimal->getX(), currMovingAnimal->getY() };
			currMovingAnimal->move(point);
			isInMovingProc = false;
			invalidateFarm();
			actionsMade.push_back(play);
		}
		else
		{
			MessageBox(_T("Animals can move only in Farm area!"));
			isInMovingProc = false;
			invalidateFarm();
		}
	}
	else
	{
		for (vector<Animal*>::iterator it = animalsVec.begin(); it != animalsVec.end(); ++it)
		{
			if ((*it)->isInside(point))
			{
				isInMovingProc = true;
				currMovingAnimal = *it;
				invalidateFarm();
			}
		}
	}


}

void COOProjectDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	for (vector<Animal*>::iterator it = animalsVec.begin(); it != animalsVec.end(); ++it)
	{
		if ((*it)->isInside(point))
		{
			isPressed = true;
			currDraggingAnimal = *it;
		}
	}
}

void COOProjectDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (PointInBoundries(point))
	{
		Action play = { currDraggingAnimal, MOVE, currDraggingAnimal->getX(), currDraggingAnimal->getY() };
		isPressed = false;
		invalidateFarm();
		actionsMade.push_back(play);
	}
	else
	{
		MessageBox(_T("Animals can move only in Farm area!"));
		isPressed = false;
		Action made = actionsMade.back();
		currDraggingAnimal->setPlace(made.originalX, made.originalY);
		invalidateFarm();
	}
}

void COOProjectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isPressed)
	{
		currDraggingAnimal->setPlace(point.x, point.y);
		invalidateFarm();
	}
}

void COOProjectDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	isInMovingProc = false;
	invalidateFarm();
}


// End of Global mouse events handling


// Image buttons
void COOProjectDlg::OnBnClickedDog()
{
	MakeAnimalSpeak<Dog>();
}

void COOProjectDlg::OnBnClickedCow()
{
	MakeAnimalSpeak<Cow>();
}

void COOProjectDlg::OnBnClickedSnake()
{
	MakeAnimalSpeak<Snake>();
}
// End of Image buttons


// Remove animal buttons
void COOProjectDlg::OnBnClickedMinusDog()
{
	DeleteAnimal<Dog>(true);
}

void COOProjectDlg::OnBnClickedMinusCow()
{
	DeleteAnimal< Cow >(true);
}

void COOProjectDlg::OnBnClickedMinusSnake()
{
	DeleteAnimal< Snake >(true);
}
// End of Remove animal buttons


void COOProjectDlg::OnBnClickedButtonUndo()
{
	if (actionsMade.size() == 0) 
	{ 
		MessageBox(_T("No available actions to UnDo!"));
		return;
	}
	Action play = actionsMade.back();
	Action redoPlay;
	actionsMade.pop_back();
	switch (play.operation)
	{
	case CREATE:
		redoPlay = { play.animal, REMOVE };
		redoActions.push_back(redoPlay);
		isInMovingProc = false;
		if (dynamic_cast<Dog*>(play.animal))
		{
			DeleteAnimal<Dog>(false);
		}
		else if (dynamic_cast<Cow*>(play.animal)) 
		{
			DeleteAnimal<Cow>(false);
		}
		else if (dynamic_cast<Snake*>(play.animal))
		{
			DeleteAnimal<Snake>(false);
		}
		break;
	case REMOVE:
		redoPlay = { play.animal, CREATE };
		redoActions.push_back(redoPlay);

		if (dynamic_cast<Dog*>(play.animal))
		{
			AddAnimal<Dog>(play.animal);
		}
		else if (dynamic_cast<Cow*>(play.animal))
		{
			AddAnimal<Cow>(play.animal);
		}
		else if (dynamic_cast<Snake*>(play.animal))
		{
			AddAnimal<Snake>(play.animal);
		}
		break;
	case MOVE:
		redoPlay = { play.animal, MOVE, play.animal->getX(), play.animal->getY()};
		redoActions.push_back(redoPlay);
		play.animal->setPlace(play.originalX, play.originalY);
		invalidateFarm();
		break;
	default:
		break;
	}
}


void COOProjectDlg::OnBnClickedButtonRedo()
{
	if (redoActions.size() == 0)
	{
		MessageBox(_T("No available actions to ReDo!"));
		return;
	}
	Action play = redoActions.back();
	Action undoPlay;
	redoActions.pop_back();
	switch (play.operation)
	{
	case CREATE:
		undoPlay = { play.animal, REMOVE };
		actionsMade.push_back(undoPlay);
		isInMovingProc = false;
		if (dynamic_cast<Dog*>(play.animal))
		{
			DeleteAnimal<Dog>(false);
		}
		else if (dynamic_cast<Cow*>(play.animal))
		{
			DeleteAnimal<Cow>(false);
		}
		else if (dynamic_cast<Snake*>(play.animal))
		{
			DeleteAnimal<Snake>(false);
		}
		break;
	case REMOVE:
		undoPlay = { play.animal, CREATE };
		actionsMade.push_back(undoPlay);

		if (dynamic_cast<Dog*>(play.animal))
		{
			AddAnimal<Dog>(play.animal);
		}
		else if (dynamic_cast<Cow*>(play.animal))
		{
			AddAnimal<Cow>(play.animal);
		}
		else if (dynamic_cast<Snake*>(play.animal))
		{
			AddAnimal<Snake>(play.animal);
		}
		break;
	case MOVE:
		undoPlay = { play.animal, MOVE, play.animal->getX(), play.animal->getY() };
		actionsMade.push_back(undoPlay);
		play.animal->setPlace(play.originalX, play.originalY);
		invalidateFarm();
		break;
	default:
		break;
	}
}


void COOProjectDlg::OnBnClickedButtonSave()
{
	// Choice and open file ostream
	CFileDialog dlg(FALSE, _TEXT("dat"), _TEXT("*.dat"));
	CString fname;
	int res = dlg.DoModal();
	if (res == IDOK)
		fname = dlg.GetPathName();

	// write to file
	CFile fOut;
	if (fOut.Open(fname, CFile::modeCreate | CFile::modeWrite))
	{
		CArchive ar(&fOut, CArchive::store);
		ar << vecSize;
		for (vector<Animal*>::iterator it = animalsVec.begin(); it != animalsVec.end(); ++it)
		{
			(*it)->Serialize(ar);
		}
		ar.Close();
	}
	fOut.Close();
	invalidateFarm();
}


void COOProjectDlg::OnBnClickedButtonLoad()
{
	// Choice and open file ostream
	CFileDialog dlg(TRUE, _TEXT("dat"), _TEXT("*.dat"));
	CString fname;
	int res = dlg.DoModal();
	if (res == IDOK)
		fname = dlg.GetPathName();

	// load to file
	CFile fOut;
	if (fOut.Open(fname, CFile::modeRead))
	{
		CArchive ar(&fOut, CArchive::load);
		animalsVec.clear();
		int newSize;
		ar >> newSize;
		for (int i = 0; i < newSize; i++) {
			int newAnimalIndex;
			ar >> newAnimalIndex;
			switch (newAnimalIndex) {
			case DOG:
				AddAnimal< Dog >();
				break;
			case COW:
				AddAnimal< Cow >();
				break;
			case SNAKE:
				AddAnimal< Snake >();
				break;
			}
			animalsVec.back()->Serialize(ar);
		}
		ar.Close();
	}
	fOut.Close();
	invalidateFarm();
}

void COOProjectDlg::invalidateFarm()
{
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_FARM);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(rect, true);
}


void COOProjectDlg::OnBnClickedButtonHELP()
{
	MessageBox(_T("MANAGE YOUR FARM! add, move and remove animals!"));
}
