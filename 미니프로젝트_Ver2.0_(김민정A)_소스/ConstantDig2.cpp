// ConstantDig2.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImage Alpha1.h"
#include "afxdialogex.h"
#include "ConstantDig2.h"


// CConstantDig2 대화 상자

IMPLEMENT_DYNAMIC(CConstantDig2, CDialog)

CConstantDig2::CConstantDig2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT2, pParent)
	, m_constant2(0)
{

}

CConstantDig2::~CConstantDig2()
{
}

void CConstantDig2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_CONSTANT2, m_constant2);
	DDV_MinMaxInt(pDX, m_constant2, 0, 5);
}


BEGIN_MESSAGE_MAP(CConstantDig2, CDialog)
END_MESSAGE_MAP()


// CConstantDig2 메시지 처리기
