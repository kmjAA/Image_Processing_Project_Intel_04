// ConstnatDig3.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImage Alpha1.h"
#include "afxdialogex.h"
#include "ConstnatDig3.h"


// CConstnatDig3 대화 상자

IMPLEMENT_DYNAMIC(CConstnatDig3, CDialog)

CConstnatDig3::CConstnatDig3(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT3, pParent)
	, m_constant3(0)
{

}

CConstnatDig3::~CConstnatDig3()
{
}

void CConstnatDig3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_CONSTANT3, m_constant3);
	DDV_MinMaxDouble(pDX, m_constant3, 0, 360);
}


BEGIN_MESSAGE_MAP(CConstnatDig3, CDialog)
	ON_EN_CHANGE(IDC_EDIT1_CONSTANT3, &CConstnatDig3::OnEnChangeEdit1Constant3)
END_MESSAGE_MAP()


// CConstnatDig3 메시지 처리기


void CConstnatDig3::OnEnChangeEdit1Constant3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
