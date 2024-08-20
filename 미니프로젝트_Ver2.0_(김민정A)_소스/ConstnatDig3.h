#pragma once
#include "afxdialogex.h"


// CConstnatDig3 대화 상자

class CConstnatDig3 : public CDialog
{
	DECLARE_DYNAMIC(CConstnatDig3)

public:
	CConstnatDig3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstnatDig3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1Constant3();
	double m_constant3;
};
