// ConstantDig1.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImage Alpha1.h"
#include "afxdialogex.h"
#include "ConstantDig1.h"


// CConstantDig1 대화 상자

IMPLEMENT_DYNAMIC(CConstantDig1, CDialog)

CConstantDig1::CConstantDig1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT1, pParent)
	, m_constant1(0)
{

}

CConstantDig1::~CConstantDig1()
{
}

void CConstantDig1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_CONSTANT1, m_constant1);
	DDV_MinMaxDouble(pDX, m_constant1, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstantDig1, CDialog)
END_MESSAGE_MAP()


// CConstantDig1 메시지 처리기
