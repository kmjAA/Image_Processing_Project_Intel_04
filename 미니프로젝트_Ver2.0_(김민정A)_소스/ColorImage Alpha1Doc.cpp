
// ColorImage Alpha1Doc.cpp: CColorImageAlpha1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImage Alpha1.h"
#endif

#include "ColorImage Alpha1Doc.h"

#include <propkey.h>
#include "ConstantDig1.h"
#include "ConstantDig2.h"
#include "ConstnatDig3.h"
#include "ConstantDig4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageAlpha1Doc

IMPLEMENT_DYNCREATE(CColorImageAlpha1Doc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageAlpha1Doc, CDocument)
END_MESSAGE_MAP()


// CColorImageAlpha1Doc 생성/소멸

CColorImageAlpha1Doc::CColorImageAlpha1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageAlpha1Doc::~CColorImageAlpha1Doc()
{
}

BOOL CColorImageAlpha1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImageAlpha1Doc serialization

void CColorImageAlpha1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageAlpha1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageAlpha1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageAlpha1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageAlpha1Doc 진단

#ifdef _DEBUG
void CColorImageAlpha1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageAlpha1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageAlpha1Doc 명령


BOOL CColorImageAlpha1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// 기존 메모리 해제
	if (m_inImageR != NULL) {
		OnFree2D(m_inImageR, m_inH);
		OnFree2D(m_inImageG, m_inH);
		OnFree2D(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 크기 알아내기~
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage의 객체값 --> 메모리
	COLORREF  px;
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}

	//OnEqualImage();
	return TRUE;
}


unsigned char** CColorImageAlpha1Doc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];

	return memory;
}


void CColorImageAlpha1Doc::OnFree2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}

double** CColorImageAlpha1Doc::OnMalloc2D_Double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** memory;
	memory = new double* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new double[w];
	return memory;
}

void CColorImageAlpha1Doc::OnFree2d_double(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}

double* CColorImageAlpha1Doc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CColorImageAlpha1Doc::HSI2RGB(double H, double S, double I)
{
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}



void CColorImageAlpha1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);

	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);

	CDocument::OnCloseDocument();
}


BOOL CColorImageAlpha1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;

	CImage image;
	image.Create(m_outW, m_outH, 32);

	unsigned char R, G, B;
	COLORREF px;

	for (int i = 0; i < m_outW; i++)
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장 성공", L"저장", NULL);

	return TRUE;
}

void CColorImageAlpha1Doc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

}

void CColorImageAlpha1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];

		}

	}
}



void CColorImageAlpha1Doc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
			

		}

	}
}




void CColorImageAlpha1Doc::OnAddImage()
{
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	int value = (int)dlg.m_constant1;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] + value > 255)
				m_outImageR[i][k] = 255;

			else if (m_inImageR[i][k] + value < 0)
				m_outImageR[i][k] = 0;

			else
				m_outImageR[i][k] = m_inImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageG[i][k] + value > 255)
				m_outImageG[i][k] = 255;

			else if (m_inImageG[i][k] + value < 0)
				m_outImageG[i][k] = 0;

			else
				m_outImageG[i][k] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageB[i][k] + value > 255)
				m_outImageB[i][k] = 255;

			else if (m_inImageB[i][k] + value < 0)
				m_outImageB[i][k] = 0;

			else
				m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnSubImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	int value = (int)dlg.m_constant1;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] - value > 255)
				m_outImageR[i][k] = 255;

			else if (m_inImageR[i][k] - value < 0)
				m_outImageR[i][k] = 0;

			else
				m_outImageR[i][k] = m_inImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageG[i][k] - value > 255)
				m_outImageG[i][k] = 255;

			else if (m_inImageG[i][k] - value < 0)
				m_outImageG[i][k] = 0;

			else
				m_outImageG[i][k] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageB[i][k] - value > 255)
				m_outImageB[i][k] = 255;

			else if (m_inImageB[i][k] - value < 0)
				m_outImageB[i][k] = 0;

			else
				m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnMulImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	int value = (int)dlg.m_constant1;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] * value > 255)
				m_outImageR[i][k] = 255;

			else if (m_inImageR[i][k] * value < 0)
				m_outImageR[i][k] = 0;

			else
				m_outImageR[i][k] = m_inImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageG[i][k] * value > 255)
				m_outImageG[i][k] = 255;

			else if (m_inImageG[i][k] * value < 0)
				m_outImageG[i][k] = 0;

			else
				m_outImageG[i][k] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageB[i][k] * value > 255)
				m_outImageB[i][k] = 255;

			else if (m_inImageB[i][k] * value < 0)
				m_outImageB[i][k] = 0;

			else
				m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


//void CColorImageAlpha1Doc::OnDivImage()
//{
//	// TODO: 여기에 구현 코드 추가.
//	CConstantDig1 dlg;
//	if (dlg.DoModal() != IDOK)
//		return;
//
//	// TODO: 여기에 구현 코드 추가.
//	//기존 메모리 해제
//	OnFreeOutImage();
//
//	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
//	m_outH = m_inH;
//	m_outW = m_inW;
//
//	//메모리 할당
//	m_outImageR = OnMalloc2D(m_outH, m_outW);
//	m_outImageG = OnMalloc2D(m_outH, m_outW);
//	m_outImageB = OnMalloc2D(m_outH, m_outW);
//
//	//진짜 영상처리 알고리즘
//
//	int value = (int)dlg.m_constant1;
//
//	for (int i = 0; i < m_outH; i++) {
//		for (int k = 0; k < m_outW; k++) {
//			if (m_inImageR[i][k] / value > 255)
//				m_outImageR[i][k] = 255;
//
//			else if (m_inImageR[i][k] / value < 0)
//				m_outImageR[i][k] = 0;
//
//			else
//				m_outImageR[i][k] = m_inImageR[i][k];
//		}
//	}
//
//	for (int i = 0; i < m_outH; i++) {
//		for (int k = 0; k < m_outW; k++) {
//			if (m_inImageG[i][k] / value > 255)
//				m_outImageG[i][k] = 255;
//
//			else if (m_inImageG[i][k] / value < 0)
//				m_outImageG[i][k] = 0;
//
//			else
//				m_outImageG[i][k] = m_inImageG[i][k];
//		}
//	}
//
//	for (int i = 0; i < m_outH; i++) {
//		for (int k = 0; k < m_outW; k++) {
//			if (m_inImageB[i][k] / value > 255)
//				m_outImageB[i][k] = 255;
//
//			else if (m_inImageB[i][k] / value < 0)
//				m_outImageB[i][k] = 0;
//
//			else
//				m_outImageB[i][k] = m_inImageB[i][k];
//		}
//	}
//}


void CColorImageAlpha1Doc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
			
		}
	}

}


void CColorImageAlpha1Doc::OnDarkImage()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] < 128)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = 255;

			if (m_inImageG[i][k] < 128)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = 255;

			if (m_inImageB[i][k] < 128)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = 255;

		}
	}
}


void CColorImageAlpha1Doc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	int value = (int)dlg.m_constant1;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageR[i][k] & value;
			if (pix > 255)
				m_outImageR[i][k] = 255;
			else if (pix < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = pix;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageG[i][k] & value;
			if (pix > 255)
				m_outImageG[i][k] = 255;
			else if (pix < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = pix;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageB[i][k] & value;
			if (pix > 255)
				m_outImageB[i][k] = 255;
			else if (pix < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = pix;
		}
	}
}


void CColorImageAlpha1Doc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	int value = (int)dlg.m_constant1;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageR[i][k] | value;
			if (pix > 255)
				m_outImageR[i][k] = 255;
			else if (pix < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = pix;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageG[i][k] | value;
			if (pix > 255)
				m_outImageG[i][k] = 255;
			else if (pix < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = pix;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageB[i][k] | value;
			if (pix > 255)
				m_outImageB[i][k] = 255;
			else if (pix < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = pix;
		}
	}
}


void CColorImageAlpha1Doc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	int value = (int)dlg.m_constant1;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageR[i][k] ^ value;
			if (pix > 255)
				m_outImageR[i][k] = 255;
			else if (pix < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = pix;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageG[i][k] ^ value;
			if (pix > 255)
				m_outImageG[i][k] = 255;
			else if (pix < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = pix;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int pix = m_inImageB[i][k] ^ value;
			if (pix > 255)
				m_outImageB[i][k] = 255;
			else if (pix < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = pix;
		}
	}
}


void CColorImageAlpha1Doc::OnZoomin()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig2 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int value = (int)dlg.m_constant2;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH * value;
	m_outW = m_inW * value;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i * value][k * value] = m_inImageR[i][k];
			m_outImageG[i * value][k * value] = m_inImageG[i][k];
			m_outImageB[i * value][k * value] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnZoomin2()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig2 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int value = (int)dlg.m_constant2;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH * value;
	m_outW = m_inW * value;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[i / value][k / value];
			m_outImageG[i][k] = m_inImageG[i / value][k / value];
			m_outImageB[i][k] = m_inImageB[i / value][k / value];
		}
	}
	
}


void CColorImageAlpha1Doc::OnZoomout()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig2 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int value = (int)dlg.m_constant2;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH / value;
	m_outW = m_inW / value;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i / value][k / value] = m_inImageR[i][k];
			m_outImageG[i / value][k / value] = m_inImageG[i][k];
			m_outImageB[i / value][k / value] = m_inImageB[i][k];
		}
	}

}


void CColorImageAlpha1Doc::OnRotate()
{
	// TODO: 여기에 구현 코드 추가.
	CConstnatDig3 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int value = (int)dlg.m_constant3;
	double radian = value * 3.141592 / 180.0;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}


void CColorImageAlpha1Doc::OnRotate2()
{
	// TODO: 여기에 구현 코드 추가.
	CConstnatDig3 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int value = (int)dlg.m_constant3;
	double radian = value * 3.141592 / 180.0;

	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	int cx = m_inH / 2;
	int cy = m_inW / 2;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int xd = i;
			int yd = k;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}


void CColorImageAlpha1Doc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig4 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int value = (int)dlg.m_constant4;
	int value2 = (int)dlg.m_constant5;
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_outH - value; i++) {
		for (int k = 0; k < m_outW - value2; k++) {
			 m_outImageR[i][k] = m_inImageR[i + value][k + value2];
			 m_outImageG[i][k] = m_inImageG[i + value][k + value2];
			 m_outImageB[i][k] = m_inImageB[i + value][k + value2];
		}
	}
}



void CColorImageAlpha1Doc::OnRotation()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][m_inW - k - 1];
			m_outImageG[i][k] = m_inImageG[i][m_inW - k - 1];
			m_outImageB[i][k] = m_inImageB[i][m_inW - k - 1];

		}

	}
}


void CColorImageAlpha1Doc::OnRotation2()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[m_inH - i - 1][k];
			m_outImageG[i][k] = m_inImageG[m_inH - i - 1][k];
			m_outImageB[i][k] = m_inImageB[m_inH - i - 1][k];

		}

	}
}


void CColorImageAlpha1Doc::OnHistoStretch()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k];
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int old = m_inImageR[i][k];
			int m_new = (int)((double)(old - lowR) / (double)(highR - lowR) * 255.0);
			if (m_new > 255)
				m_new = 255;
			if (m_new < 0)
				m_new = 0;
			m_outImageR[i][k] = m_new;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k];
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];
		}
	}


	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int old = m_inImageG[i][k];
			int m_new = (int)((double)(old - lowG) / (double)(highG - lowG) * 255.0);
			if (m_new > 255)
				m_new = 255;
			if (m_new < 0)
				m_new = 0;
			m_outImageG[i][k] = m_new;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k];
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {


			int old = m_inImageB[i][k];
			int m_new = (int)((double)(old - lowB) / (double)(highB - lowB) * 255.0);
			if (m_new > 255)
				m_new = 255;
			if (m_new < 0)
				m_new = 0;
			m_outImageB[i][k] = m_new;
		}
	}
}


void CColorImageAlpha1Doc::OnEndin()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	int value = (int)dlg.m_constant1;
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k];
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];
		}
	}

	highR -= value;
	lowR += value;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int old = m_inImageR[i][k];
			int m_new = (int)((double)(old - lowR) / (double)(highR - lowR) * 255.0);
			if (m_new > 255)
				m_new = 255;
			if (m_new < 0)
				m_new = 0;
			m_outImageR[i][k] = m_new;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k];
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];
		}
	}
	highG -= value;
	lowG += value;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int old = m_inImageG[i][k];
			int m_new = (int)((double)(old - lowG) / (double)(highG - lowG) * 255.0);
			if (m_new > 255)
				m_new = 255;
			if (m_new < 0)
				m_new = 0;
			m_outImageG[i][k] = m_new;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k];
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}

	highB -= value;
	lowB += value;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {


			int old = m_inImageB[i][k];
			int m_new = (int)((double)(old - lowB) / (double)(highB - lowB) * 255.0);
			if (m_new > 255)
				m_new = 255;
			if (m_new < 0)
				m_new = 0;
			m_outImageB[i][k] = m_new;
		}
	}
}




void CColorImageAlpha1Doc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	//기존 메모리 해제
	OnFreeOutImage();

	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;

	//메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	int histoR[256] = { 0, }; int histoG[256] = { 0, }; int histoB[256] = { 0, };
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	}

	int sumhistoR[256] = { 0, }; int sumhistoG[256] = { 0, }; int sumhistoB[256] = { 0, };
	sumhistoR[0] = histoR[0]; sumhistoG[0] = histoG[0]; sumhistoB[0] = histoB[0];
	for (int i = 0; i < 256; i++) {
		sumhistoR[i] = sumhistoR[i - 1] + histoR[i];
		sumhistoG[i] = sumhistoG[i - 1] + histoG[i];
		sumhistoB[i] = sumhistoB[i - 1] + histoB[i];
	}

	double normalhistoR[256] = { 1.0, }; double normalhistoG[256] = { 1.0, }; double normalhistoB[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalhistoR[i] = sumhistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalhistoG[i] = sumhistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalhistoB[i] = sumhistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)normalhistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = (unsigned char)normalhistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = (unsigned char)normalhistoB[m_inImageB[i][k]];
		}
	}
}


void CColorImageAlpha1Doc::OnEmbossRgb()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 마스크
						  {0.0, 0.0, 0.0},
						  {0.0, 0.0, 1.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}
	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);

}



void CColorImageAlpha1Doc::OnEmbossHsi()
{
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 마스크
						  {0.0, 0.0, 0.0},
						  {0.0, 0.0, 1.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_Double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}



	//RGB->HSI
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_Value = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_Value += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_Value;

		}
	}
	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127;
		}

	//HSI->RGB
	for(int i =0; i<m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpInImageH, m_inH + 2);
	OnFree2d_double(tmpInImageS, m_inH + 2);
	OnFree2d_double(tmpInImageI, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);

}




void CColorImageAlpha1Doc::OnBlurr()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {1. / 9,1. / 9,1. / 9}, //마스크
						  {1. / 9,1. / 9,1. / 9},
						  {1. / 9,1. / 9,1. / 9} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);

}


void CColorImageAlpha1Doc::OnBlurr2()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[9][9] = { {1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 8, m_inW + 8);
	tmpInImageG = OnMalloc2D_Double(m_inH + 8, m_inW + 8);
	tmpInImageB = OnMalloc2D_Double(m_inH + 8, m_inW + 8);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 8; i++)
		for (int k = 0; k < m_inW + 8; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 8; m++)
				for (int n = 0; n < 8; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 8; m++)
				for (int n = 0; n < 8; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 8; m++)
				for (int n = 0; n < 8; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 8);
	OnFree2d_double(tmpInImageG, m_inH + 8);
	OnFree2d_double(tmpInImageB, m_inH + 8);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);

}

void CColorImageAlpha1Doc::OnSmoot()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {1. / 16, 1. / 8, 1. / 16}, //마스크
						  {1. / 8, 1. / 4, 1. / 8},
						  {1. / 16, 1. / 8, 1. / 16} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}




void CColorImageAlpha1Doc::OnSharp1()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {-1, -1, -1}, //마스크
						  {-1,  9, -1},
						  {-1, -1, -1} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSharp2()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {0, -1, 0}, //마스크
						  {-1, 5, -1},
						  {0, -1, -0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSharp3()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {-1. / 9, -1. / 9, -1. / 9}, //마스크
						  {-1. / 9, 8. / 9, -1. / 9},
						  {-1. / 9, -1. / 9, -1. / 9} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}




void CColorImageAlpha1Doc::OnEdge1()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;

	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {0.0, 0.0, 0.0}, // 수직 에지 검출마스크
						  {-1.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	/*for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}*/

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge2()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {0.0, -1.0, 0.0}, // 수평 에지 검출마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	/*for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}*/

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge4()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {0.0, -1.0, -2.0}, // 프리윗 에지 검출마스크
						  {1.0, 0.0, -1.0},
						  {2.0, 1.0, 0.0} };

	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	/*for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}*/

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge5()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {-1.0, 0.0, -1.0}, // 로버츠 에지 검출마스크
						  {0.0, 2.0, 0.0},
						  {0.0, 0.0, 0.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	/*for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}*/

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}



void CColorImageAlpha1Doc::OnEdge6()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {0.0, -2.0, -2.0}, // 소벨 에지 검출마스크
						  {2.0, 0.0, -2.0},
						  {2.0, 2.0, 0.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	/*for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}*/

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge7()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	//진짜 영상처리 알고리즘
	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 라플라시안 마스크
						  {-1.0, 8.0, -1.0},
						  {-1.0, -1.0, -1.0} };


	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_Double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_Double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_Double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}


	//// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	//for (int i = 0; i < m_inH; i++)
	//	for (int k = 0; k < m_inW; k++) {
	//		tmpOutImageR[i][k] += 127;
	//		tmpOutImageG[i][k] += 127;
	//		tmpOutImageB[i][k] += 127;
	//	}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d_double(tmpInImageR, m_inH + 2);
	OnFree2d_double(tmpInImageG, m_inH + 2);
	OnFree2d_double(tmpInImageB, m_inH + 2);
	OnFree2d_double(tmpOutImageR, m_outH);
	OnFree2d_double(tmpOutImageG, m_outH);
	OnFree2d_double(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];	S = hsi[1];	I = hsi[2];

			/// 채도(S) 흐리게
			S = S - 0.3;
			if (S < 0)
				S = 0.0;

			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}


void CColorImageAlpha1Doc::OnOrange()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];	S = hsi[1];	I = hsi[2];

			/// 오렌지 추출 (H : 8~20)
			if (8 <= H && H <= 20) {
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			else {
				double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
			}

		}
	}
}
