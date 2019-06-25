#pragma once
#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>
#include "ToolMain.h"
#include "Game.h"

// SelectDialogue dialog

class ObjectInspector : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectInspector)


public:
	ObjectInspector(CWnd* pParent, std::vector<SceneObject> SceneGraph);   // modal // takes in out scenegraph in the constructor
	ObjectInspector(CWnd* pParent = NULL);
	virtual ~ObjectInspector();
	void SetObjectData(std::vector<SceneObject> SceneGraph, int * Selection, ToolMain *m_ToolSystem);	//passing in pointers to the data the class will operate on.


																				// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void Select();	//Item has been selected
	afx_msg void InitTextBoxes();
	afx_msg void OnCancel();

	std::vector<SceneObject>  m_sceneGraph;
	int * m_currentSelection;

	Game* game;
	ToolMain* toolmain;

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_edit_posX;
	CEdit m_edit_posY;
	CEdit m_edit_posZ;
	CEdit m_edit_scaleX;
	CEdit m_edit_scaleY;
	CEdit m_edit_scaleZ;
	CEdit m_edit_rotX;
	CEdit m_edit_rotY;
	CEdit m_edit_rotZ;


	// Control variable for more efficient access of the listbox
	CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void EditXPos();
	afx_msg void EditYPos();
	afx_msg void EditZPos();
	afx_msg void EditXScale();
	afx_msg void EditYScale();
	afx_msg void EditZScale();
	afx_msg void EditXRot();
	afx_msg void EditYRot();
	afx_msg void EditZRot();
	afx_msg void ReturnObjectDataWithID(SceneObject& object);
};


INT_PTR CALLBACK SelectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);
