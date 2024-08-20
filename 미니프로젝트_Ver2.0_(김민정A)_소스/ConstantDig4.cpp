// ConstantDig4.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImage Alpha1.h"
#include "afxdialogex.h"
#include "ConstantDig4.h"


// CConstantDig4 대화 상자

IMPLEMENT_DYNAMIC(CConstantDig4, CDialog)

CConstantDig4::CConstantDig4(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT4, pParent)
	, m_constant4(0)
	, m_constant4_2(0)
	, m_constant5(0)
{

}

CConstantDig4::~CConstantDig4()
{
}

void CConstantDig4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_CONSTANT4, m_constant4);
	DDV_MinMaxDouble(pDX, m_constant4, 0, 300);
	
	DDV_MinMaxDouble(pDX, m_constant4_2, 0, 300);
	DDX_Text(pDX, IDC_EDIT2_CONSTANT5, m_constant5);
	DDV_MinMaxDouble(pDX, m_constant5, 0, 300);
}


BEGIN_MESSAGE_MAP(CConstantDig4, CDialog)
	ON_EN_CHANGE(IDC_EDIT1_CONSTANT4, &CConstantDig4::OnEnChangeEdit1Constant4)
	
END_MESSAGE_MAP()


// CConstantDig4 메시지 처리기


void CConstantDig4::OnEnChangeEdit1Constant4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CConstantDig4::OnEnChangeEdit2Constant4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
