#pragma once
#include "afxdialogex.h"


// CConstantDig1 대화 상자

class CConstantDig1 : public CDialog
{
	DECLARE_DYNAMIC(CConstantDig1)

public:
	CConstantDig1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDig1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant1;
};
