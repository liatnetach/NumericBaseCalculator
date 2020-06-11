
// NumericBaseCalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NumericBaseCalculator.h"
#include "NumericBaseCalculatorDlg.h"
#include "afxdialogex.h"
#include "Polynom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
using namespace std;
#include <iostream>
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNumericBaseCalculatorDlg dialog



CNumericBaseCalculatorDlg::CNumericBaseCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMERICBASECALCULATOR_DIALOG, pParent)
	, formula(_T(""))
	, isBinary(FALSE)
	, isOctal(FALSE)
	, isDec(TRUE)
	, isHex(FALSE)
	, binDisp(_T(""))
	, octDisp(_T(""))
	, decDisp(_T(""))
	, hexDisp(_T(""))
	, memory(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isOperatorExist = false;
	justResulted = false;
	base[0] = new BinaryBase;
	base[1] = new OctalBase;
	base[2] = new DecimalBase;
	base[3] = new HexadecimalBase;
	curBase = base[2];
}

void CNumericBaseCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, formula);
	DDX_Text(pDX, IDC_EDIT6, binDisp);
	DDX_Text(pDX, IDC_EDIT8, octDisp);
	DDX_Text(pDX, IDC_EDIT7, decDisp);
	DDX_Text(pDX, IDC_EDIT9, hexDisp);
	DDX_Text(pDX, IDC_EDIT1, memory);
}

BEGIN_MESSAGE_MAP(CNumericBaseCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON11, &CNumericBaseCalculatorDlg::OnBnClickedButton11)
	ON_EN_CHANGE(IDC_EDIT2, &CNumericBaseCalculatorDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CNumericBaseCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNumericBaseCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CNumericBaseCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CNumericBaseCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CNumericBaseCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CNumericBaseCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CNumericBaseCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CNumericBaseCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CNumericBaseCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CNumericBaseCalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON18, &CNumericBaseCalculatorDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON17, &CNumericBaseCalculatorDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON16, &CNumericBaseCalculatorDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &CNumericBaseCalculatorDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON14, &CNumericBaseCalculatorDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON25, &CNumericBaseCalculatorDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON19, &CNumericBaseCalculatorDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CNumericBaseCalculatorDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CNumericBaseCalculatorDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CNumericBaseCalculatorDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CNumericBaseCalculatorDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CNumericBaseCalculatorDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON12, &CNumericBaseCalculatorDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_RADIO1, &CNumericBaseCalculatorDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CNumericBaseCalculatorDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CNumericBaseCalculatorDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CNumericBaseCalculatorDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON26, &CNumericBaseCalculatorDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON13, &CNumericBaseCalculatorDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON27, &CNumericBaseCalculatorDlg::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CNumericBaseCalculatorDlg::OnBnClickedButton28)
END_MESSAGE_MAP()


// CNumericBaseCalculatorDlg message handlers

BOOL CNumericBaseCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		this->CheckRadioButton(IDC_RADIO1, IDC_RADIO4, IDC_RADIO3);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNumericBaseCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNumericBaseCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	if (!curBase->lastFormula.IsEmpty())
	{
		int size = curBase->lastFormula.GetLength();
		CString c = curBase->lastFormula;
		c.Delete(0, size - 1);//only the last char remain
		curBase->lastFormula.Delete(size - 1, 1);
		this->arrInit();
		CWnd *btn;
		if (c == '0')
		{
			isBinary = true;
			isOctal = false;
			isDec = false;
			isHex = false;
			curBase = base[0];
			for (int i = 2; i <= 15; i++)
			{
				btn = arrBtn[i];
				btn->EnableWindow(FALSE);
			}
			this->CheckRadioButton(IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);
		}
		else if (c == '1')
		{
			isBinary = false;
			isOctal = true;
			isDec = false;
			isHex = false;
			curBase = base[1];
			for (int i = 8; i <= 15; i++)
			{
				btn = arrBtn[i];
				btn->EnableWindow(FALSE);
			}
			this->CheckRadioButton(IDC_RADIO1, IDC_RADIO4, IDC_RADIO2);
		}
		else if (c == '2')
		{
			isBinary = false;
			isOctal = false;
			isDec = true;
			isHex = false;
			curBase = base[2];
			for (int i = 10; i <= 15; i++)
			{
				btn = arrBtn[i];
				btn->EnableWindow(FALSE);
			}
			this->CheckRadioButton(IDC_RADIO1, IDC_RADIO4, IDC_RADIO3);
		}
		else if (c == '3')
		{
			isBinary = false;
			isOctal = false;
			isDec = false;
			isHex = true;
			curBase = base[3];
			this->CheckRadioButton(IDC_RADIO1, IDC_RADIO4, IDC_RADIO4);
		}
		formula = curBase->lastFormula;
		c = curBase->baseToDec(curBase->lastFormula);
		binDisp = base[0]->print(c);
		octDisp = base[1]->print(c);
		hexDisp = base[3]->print(c);
		decDisp = base[2]->print(c);
		UpdateData(false);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNumericBaseCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNumericBaseCalculatorDlg::OnBnClickedButton11()
{
	UpdateData(true);
	formula.Delete(formula.GetLength() - 1, 1);
	UpdateData(false);
}

void CNumericBaseCalculatorDlg::OnEnChangeEdit2()
{
}


void CNumericBaseCalculatorDlg::OnBnClickedButton1()
{
	UpdateData(true);
	if (justResulted) 
	{ 
		justResulted = 0; 
		formula = '1';
	}
	else formula += '1';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton2()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '2';
	}
	else formula += '2';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton3()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '3';
	}
	else formula += '3';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton4()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '4';
	}
	else formula += '4';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton5()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '5';
	}
	else formula += '5';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton6()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '6';
	}
	else formula += '6';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton7()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '7';
	}
	else formula += '7';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton8()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = "8";
	}
	else formula += '8';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton9()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = '9';
	}
	else formula += '9';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton10()
{
	UpdateData(true);
	int size = formula.GetLength();
	if (justResulted)
	{
		justResulted = 0;
		formula = '0';
	}
	else if(formula[size - 1] != '/') 
		formula += '0';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton18()
{
	UpdateData(true);
	int size = formula.GetLength();
	if (!(formula.IsEmpty())&&((formula[size - 1]>='0' && formula[size - 1] <= '9')||(formula[size - 1] >= 'A' && formula[size - 1] <= 'F')))
	{
		formula += '^';
		if (justResulted)justResulted = 0;
	}
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton17()
{
	UpdateData(true);
	if (!(formula.IsEmpty()))
	{	
		int size = formula.GetLength();
		if (formula[size - 1] >= '0' && formula[size - 1] <= '9')
		{
			if (isOperatorExist)
			{
				calcs(formula);
			}
			else
			{
				isOperatorExist = 1;
				justResulted = 0;
			}
		}
		else if (formula[size - 1] == '-' || formula[size - 1] == '*' || formula[size - 1] == '+' || formula[size - 1] == '/')
		{
			formula.Delete(size - 1, 1);
		}
		size = formula.GetLength();
		if (formula[size - 1] != '^')formula += '/';
		UpdateData(false);
	}
	
}


void CNumericBaseCalculatorDlg::OnBnClickedButton16()
{
	UpdateData(true);
	if (!(formula.IsEmpty()))
	{
		int size = formula.GetLength();
		if (formula[size - 1] >= '0' && formula[size - 1] <= '9')
		{
			if (isOperatorExist)
			{
				calcs(formula);
			}
			else
			{
				isOperatorExist = 1;
				justResulted = 0;
			}
		}
		else if (formula[size - 1] == '-' || formula[size - 1] == '+' || formula[size - 1] == '/' || formula[size - 1] == '*')
		{
			formula.Delete(size - 1, 1);
		}
		size = formula.GetLength();
		if (formula[size-1] != '^')formula += '*';
		UpdateData(false);
	}
}


void CNumericBaseCalculatorDlg::OnBnClickedButton15()
{
	UpdateData(true);
	if (!(formula.IsEmpty()))
	{
		int size = formula.GetLength();
		if (formula[size - 1] >= '0' && formula[size - 1] <= '9')
		{
			if (isOperatorExist)
			{
				calcs(formula);
			}
			else
			{
				isOperatorExist = 1;
				justResulted = 0;
			}
		}
		else if (formula[size - 1] == '+' || formula[size - 1] == '*' || formula[size - 1] == '/' || formula[size - 1] == '-')
		{
			formula.Delete(size - 1, 1);
		}
		size = formula.GetLength();
		if (formula[size - 1] != '^')formula += '-';
		UpdateData(false);
	}
}


void CNumericBaseCalculatorDlg::OnBnClickedButton14()
{
	UpdateData(true);
	if (!(formula.IsEmpty()))
	{
		int size = formula.GetLength();
		if (formula[size - 1] >= '0' && formula[size - 1] <= '9')
		{
			if (isOperatorExist)
			{
				calcs(formula);
			}
			else
			{
				isOperatorExist = 1;
				justResulted = 0;
			}
		}
		else if (formula[size - 1] =='-'|| formula[size - 1] == '*'||formula[size - 1] == '/' || formula[size - 1] == '+')
		{
			formula.Delete(size - 1, 1);
		}
		size = formula.GetLength();
		if (formula[size - 1] != '^')formula += '+';
		UpdateData(false);
	}
}


void CNumericBaseCalculatorDlg::OnBnClickedButton25()
{
	UpdateData(true);
	int size = formula.GetLength();
	if (!(formula.IsEmpty()))
	{
		if (formula[size - 1] == '^')
			formula.Delete(size - 1, 1);
		else 
		{
			justResulted = 1;
			isOperatorExist = 0;
			calcs(formula);
		}
	}
	else formula = "0";
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton19()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = 'A';
	}
	else formula += 'A';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton20()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = 'B';
	}
	else formula += 'B';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton21()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = 'C';
	}
	else formula += 'C';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton22()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = 'D';
	}
	else formula += 'D';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton23()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = 'E';
	}
	else formula += 'E';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton24()
{
	UpdateData(true);
	if (justResulted)
	{
		justResulted = 0;
		formula = 'F';
	}
	else formula += 'F';
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton12()
{
	UpdateData(true);
	formula = "";
	binDisp = "";
	octDisp = "";
	decDisp = "";
	hexDisp = "";
	UpdateData(false);
}




void CNumericBaseCalculatorDlg::OnBnClickedRadio1()
{
	isBinary = true;
	isOctal = false;
	isDec = false;
	isHex = false;
	curBase = base[0];
	formula = binDisp;
	UpdateData(false);
	this->arrInit();
	CWnd *btn;
	for (int i = 2; i <= 15; i++)
	{
		btn = arrBtn[i];
		btn->EnableWindow(FALSE);
	}

}


void CNumericBaseCalculatorDlg::OnBnClickedRadio2()
{
	isOctal = true;
	isBinary = false;
	isDec = false;
	isHex = false;
	curBase = base[1];
	formula = octDisp;
	UpdateData(false);
	this->arrInit();
	CWnd *btn;
	for (int i = 8; i <= 15; i++)
	{
		btn = arrBtn[i];
		btn->EnableWindow(FALSE);
	}
}


void CNumericBaseCalculatorDlg::OnBnClickedRadio3()
{
	isDec = true;
	isHex = false;
	isOctal = false;
	isBinary = false;
	curBase = base[2];
	formula = decDisp;
	UpdateData(false);
	this->arrInit();
	CWnd *btn;
	for (int i = 10; i <= 15; i++)
	{
		btn = arrBtn[i];
		btn->EnableWindow(FALSE);
	}
}

void CNumericBaseCalculatorDlg::OnBnClickedRadio4()
{
	isHex = true;
	isOctal = false;
	isBinary = false;
	isDec = false;
	curBase = base[3];
	formula = hexDisp;
	UpdateData(false);
	this->arrInit();
}

void CNumericBaseCalculatorDlg::OnBnClickedButton26()
{
	UpdateData(true);
	if(!(formula.IsEmpty()))
	{
		memory += formula;
		memory += "\r\n";
	}
	UpdateData(false);
	
}

void CNumericBaseCalculatorDlg::OnBnClickedButton13()
{
	memory = "";
	UpdateData(false);
}


void CNumericBaseCalculatorDlg::OnBnClickedButton27()//saveToFile
{
	CFile file(L"FILE.$$", CFile::modeWrite | CFile::modeCreate);
	CArchive ar(&file, CArchive::store);
	curBase->Serialize(ar);
	ar.Close();
	file.Close();
}


void CNumericBaseCalculatorDlg::OnBnClickedButton28()//loadToFile
{
	CFile file(L"FILE.$$", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	curBase->Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();
}
