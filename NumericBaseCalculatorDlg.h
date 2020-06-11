
// NumericBaseCalculatorDlg.h : header file
//

#pragma once
#include "Polynom.h"


// CNumericBaseCalculatorDlg dialog
class CNumericBaseCalculatorDlg : public CDialogEx
{
	// Construction
public:
	CNumericBaseCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMERICBASECALCULATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton11();
	afx_msg void OnEnChangeEdit2();
	CString formula;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton12();
	BOOL isBinary;
	BOOL isOctal;
	BOOL isDec;
	BOOL isHex;
	BOOL isOperatorExist;
	BOOL justResulted;
	Monom * base[4];
	Monom * curBase;
	CWnd ** arrBtn = new CWnd*[17];
	void arrInit()
	{
		arrBtn[1] = GetDlgItem(IDC_BUTTON1);
		arrBtn[2] = GetDlgItem(IDC_BUTTON2);
		arrBtn[3] = GetDlgItem(IDC_BUTTON3);
		arrBtn[4] = GetDlgItem(IDC_BUTTON4);
		arrBtn[5] = GetDlgItem(IDC_BUTTON5);
		arrBtn[6] = GetDlgItem(IDC_BUTTON6);
		arrBtn[7] = GetDlgItem(IDC_BUTTON7);
		arrBtn[8] = GetDlgItem(IDC_BUTTON8);
		arrBtn[9] = GetDlgItem(IDC_BUTTON9);
		arrBtn[0] = GetDlgItem(IDC_BUTTON10);
		arrBtn[10] = GetDlgItem(IDC_BUTTON19);
		arrBtn[11] = GetDlgItem(IDC_BUTTON20);
		arrBtn[12] = GetDlgItem(IDC_BUTTON21);
		arrBtn[13] = GetDlgItem(IDC_BUTTON22);
		arrBtn[14] = GetDlgItem(IDC_BUTTON23);
		arrBtn[15] = GetDlgItem(IDC_BUTTON24);
		for (int i = 0; i <= 15; i++)
			arrBtn[i]->EnableWindow(TRUE);
	}
	void calcs(CString& formula)
	{
		CString temp;
		temp = curBase->baseToDec(formula);
		formula = curBase->print(temp);
		binDisp = base[0]->print(temp);
		octDisp = base[1]->print(temp);
		hexDisp = base[3]->print(temp);
		decDisp = base[2]->print(temp);
	}
	CString binDisp;
	CString octDisp;
	CString decDisp;
	CString hexDisp;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton26();
	CString memory;
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();

};
