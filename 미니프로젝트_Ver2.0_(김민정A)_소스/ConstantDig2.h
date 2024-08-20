#pragma once
#include "afxdialogex.h"


// CConstantDig2 대화 상자

class CConstantDig2 : public CDialog
{
	DECLARE_DYNAMIC(CConstantDig2)

public:
	CConstantDig2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDig2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constant2;
};
