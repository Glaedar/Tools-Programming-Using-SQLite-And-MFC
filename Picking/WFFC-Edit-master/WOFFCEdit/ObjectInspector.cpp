// SelectDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "ObjectInspector.h"

// SelectDialogue dialog

IMPLEMENT_DYNAMIC(ObjectInspector, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(ObjectInspector, CDialogEx)
	ON_COMMAND(IDOK, &ObjectInspector::End)					//ok button
	ON_BN_CLICKED(IDOK, &ObjectInspector::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &ObjectInspector::Select)
	ON_EN_CHANGE(IDC_POSX, &ObjectInspector::EditXPos)
	ON_EN_CHANGE(IDC_POSY, &ObjectInspector::EditYPos)
	ON_EN_CHANGE(IDC_POSZ, &ObjectInspector::EditZPos)
	ON_EN_CHANGE(IDC_SCALEX, &ObjectInspector::EditXScale)
	ON_EN_CHANGE(IDC_SCALEY, &ObjectInspector::EditYScale)
	ON_EN_CHANGE(IDC_SCALEZ, &ObjectInspector::EditZScale)
	ON_EN_CHANGE(IDC_ROTX, &ObjectInspector::EditXRot)
	ON_EN_CHANGE(IDC_ROTY, &ObjectInspector::EditYRot)
	ON_EN_CHANGE(IDC_ROTZ, &ObjectInspector::EditZRot)




	//listbox
END_MESSAGE_MAP()


ObjectInspector::ObjectInspector(CWnd* pParent, std::vector<SceneObject> SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_sceneGraph = SceneGraph;
}

ObjectInspector::ObjectInspector(CWnd * pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
}

ObjectInspector::~ObjectInspector()
{
}

void ObjectInspector::OnCancel()
{
	CDialog::OnCancel();
	DestroyWindow();
}


///pass through pointers to the data in the tool we want to manipulate
void ObjectInspector::SetObjectData(std::vector<SceneObject> SceneGraph, int * selection, ToolMain *m_ToolSystem)
{
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;
	
	InitTextBoxes();

}


void ObjectInspector::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POSX, m_edit_posX);
	DDX_Control(pDX, IDC_POSY, m_edit_posY);
	DDX_Control(pDX, IDC_POSZ, m_edit_posZ);

	DDX_Control(pDX, IDC_SCALEX, m_edit_scaleX);
	DDX_Control(pDX, IDC_SCALEY, m_edit_scaleY);
	DDX_Control(pDX, IDC_SCALEZ, m_edit_scaleZ);

	DDX_Control(pDX, IDC_ROTX, m_edit_rotX);
	DDX_Control(pDX, IDC_ROTY, m_edit_rotY);
	DDX_Control(pDX, IDC_ROTZ, m_edit_rotZ);
}

void ObjectInspector::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void ObjectInspector::Select()
{
	int index = m_listBox.GetCurSel();
	CString currentSelectionValue;

	m_listBox.GetText(index, currentSelectionValue);

	*m_currentSelection = _ttoi(currentSelectionValue);

}

void ObjectInspector::InitTextBoxes()
{
	CString text;


	CEdit* POSX = (CEdit*)GetDlgItem(IDC_POSX);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).posX);
	POSX->ReplaceSel(text);


	CEdit* POSY = (CEdit*)GetDlgItem(IDC_POSY);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).posY);
	POSY->ReplaceSel(text);


	CEdit* POSZ = (CEdit*)GetDlgItem(IDC_POSZ);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).posZ);
	POSZ->ReplaceSel(text);

	CEdit* SCALEX = (CEdit*)GetDlgItem(IDC_SCALEX);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).scaX);
	SCALEX->ReplaceSel(text);


	CEdit* SCALEY = (CEdit*)GetDlgItem(IDC_SCALEY);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).scaY);
	SCALEY->ReplaceSel(text);


	CEdit* SCALEZ = (CEdit*)GetDlgItem(IDC_SCALEZ);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).scaZ);
	SCALEZ->ReplaceSel(text);

	CEdit* ROTX = (CEdit*)GetDlgItem(IDC_ROTX);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).rotX);
	ROTX->ReplaceSel(text);


	CEdit* ROTY = (CEdit*)GetDlgItem(IDC_ROTY);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).rotY);
	ROTY->ReplaceSel(text);


	CEdit* ROTZ = (CEdit*)GetDlgItem(IDC_ROTZ);
	text.Format(_T("%f"), m_sceneGraph.at(*m_currentSelection).rotZ);
	ROTZ->ReplaceSel(text);


}

BOOL ObjectInspector::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//uncomment for modal only
	/*	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (size_t i = 0; i < numSceneObjects; i++)
	{
	//easily possible to make the data string presented more complex. showing other columns.
	std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
	m_listBox.AddString(listBoxEntry.c_str());
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void ObjectInspector::PostNcDestroy()
{

}




// SelectDialogue message handlers callback   - We only need this if the dailogue is being setup-with createDialogue().  We are doing
//it manually so its better to use the messagemap
/*INT_PTR CALLBACK SelectProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
switch (uMsg)
{
case WM_COMMAND:
switch (LOWORD(wParam))
{
case IDOK:
//	EndDialog(hwndDlg, wParam);
DestroyWindow(hwndDlg);
return TRUE;


case IDCANCEL:
EndDialog(hwndDlg, wParam);
return TRUE;
break;
}
}

return INT_PTR();
}*/


void ObjectInspector::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void ObjectInspector::EditXPos()
{
	CString x_position_string;
	m_edit_posX.GetWindowTextW(x_position_string);
	m_sceneGraph.at(*m_currentSelection).posX = _ttof(x_position_string);
}

void ObjectInspector::EditYPos()
{
	CString y_position_string;
	m_edit_posY.GetWindowTextW(y_position_string);
	m_sceneGraph.at(*m_currentSelection).posY = _ttof(y_position_string);
}

void ObjectInspector::EditZPos()
{
	CString z_position_string;
	m_edit_posZ.GetWindowTextW(z_position_string);
	m_sceneGraph.at(*m_currentSelection).posZ = _ttof(z_position_string);
}

void ObjectInspector::EditXScale()
{
	CString x_scale_string;
	m_edit_scaleX.GetWindowTextW(x_scale_string);
	m_sceneGraph.at(*m_currentSelection).scaX = _ttof(x_scale_string);
}

void ObjectInspector::EditYScale()
{
	CString y_scale_string;
	m_edit_scaleY.GetWindowTextW(y_scale_string);
	m_sceneGraph.at(*m_currentSelection).scaY = _ttof(y_scale_string);
}

void ObjectInspector::EditZScale()
{
	CString z_scale_string;
	m_edit_scaleZ.GetWindowTextW(z_scale_string);
	m_sceneGraph.at(*m_currentSelection).scaZ = _ttof(z_scale_string);
}

void ObjectInspector::EditXRot()
{
	CString x_rot_string;
	m_edit_rotX.GetWindowTextW(x_rot_string);
	m_sceneGraph.at(*m_currentSelection).rotX = _ttof(x_rot_string);
}

void ObjectInspector::EditYRot()
{
	CString y_rot_string;
	m_edit_rotY.GetWindowTextW(y_rot_string);
	m_sceneGraph.at(*m_currentSelection).rotY = _ttof(y_rot_string);
}

void ObjectInspector::EditZRot()
{
	CString z_rot_string;
	m_edit_rotZ.GetWindowTextW(z_rot_string);
	m_sceneGraph.at(*m_currentSelection).rotZ = _ttof(z_rot_string);
}

void ObjectInspector::ReturnObjectDataWithID(SceneObject& object)
{
	if (*m_currentSelection != -1)
	{
		object = m_sceneGraph.at(*m_currentSelection);
	}
	
}
