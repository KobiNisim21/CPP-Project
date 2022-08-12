
// OOProjectDlg.h : header file
//
#pragma once
#include "Animal.h"
#include <list>
#include <vector>

using namespace std;

#ifndef DEFAULT_SPEAK
#define DEFAULT_SPEAK "Click on animal picture to make them speak!"
#endif // !DEFAULT_SPEAK

#ifndef Operations
enum Operations { CREATE = 1, REMOVE = 2, MOVE = 3 };
#endif // !Operations

#ifndef AnimalsDict
enum AnimalsDict { DOG = 1, COW = 2 , SNAKE = 3 };
#endif // !AnimalsDict

#ifndef Action
struct Action {
	Animal* animal;
	Operations operation;
	double originalX;
	double originalY;
};
#endif // !Action


// COOProjectDlg dialog

class COOProjectDlg : public CDialogEx
{
// Construction
public:
	COOProjectDlg(CWnd* pParent = nullptr);	// standard constructor
	~COOProjectDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OOPROJECT_DIALOG };
#endif
	Animal* currMovingAnimal;
	Animal* currDraggingAnimal;
	vector<Animal*> animalsVec;
	int vecSize;
	bool isInMovingProc;
	bool isPressed;
	vector<Action> actionsMade;
	vector<Action> redoActions;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CPoint GetRandomizedPosition();
	bool PointInBoundries(CPoint&);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CButton dogButtonIcon;
	CBitmap dogButtonBitmap;
	CButton cowButtonIcon;
	CBitmap cowButtonBitmap;
	CButton snakeButtonIcon;
	CBitmap snakeButtonBitmap;
	CButton plusDogButton;
	CBitmap plusButtonBitmap;
	CButton plusCowButton;
	CButton plusSnakeButton;
	CButton minusDogButton;
	CButton minusCowButton;
	CButton minusSnakeButton;
	CBitmap minusButtonBitmap;
	CButton undoButton;
	CButton redoButton;
	CBitmap redoButtonBitmap;
	CBitmap undoButtonBitmap;
	CButton loadButton;
	CBitmap loadButtonBitmap;
	CButton saveButton;
	CBitmap saveButtonBitmap;
	afx_msg void OnBnClickedPlusDog();
	CStatic farmBox;
	afx_msg void OnBnClickedPlusCow();
	afx_msg void OnBnClickedPlusSnake();
	//afx_msg void OnBnClickedFarm();
	CString speakTextBox;
	afx_msg void OnBnClickedDog();
	afx_msg void OnBnClickedCow();
	afx_msg void OnBnClickedSnake();
	template<typename T>
	void DeleteAnimal(bool);
	template<typename T>
	void AddAnimal();
	template<typename T>
	void AddAnimal(Animal*);
	template<typename T>
	void MakeAnimalSpeak();
	afx_msg void OnBnClickedMinusDog();
	afx_msg void OnBnClickedMinusCow();
	afx_msg void OnBnClickedMinusSnake();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonRedo();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	void invalidateFarm();
	afx_msg void OnBnClickedButtonHELP();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
