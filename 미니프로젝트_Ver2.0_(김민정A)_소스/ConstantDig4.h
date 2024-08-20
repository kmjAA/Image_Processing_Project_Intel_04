#pragma once
#include "afxdialogex.h"


// CConstantDig4 대화 상자

class CConstantDig4 : public CDialog
{
	DECLARE_DYNAMIC(CConstantDig4)

public:
	CConstantDig4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDig4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1Constant4();
	double m_constant4;
	afx_msg void OnEnChangeEdit2Constant4();
	double m_constant4_2;
	double m_constant5;
};
