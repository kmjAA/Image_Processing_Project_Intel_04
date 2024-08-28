
// ColorImage Alpha1View.cpp: CColorImageAlpha1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImage Alpha1.h"
#endif

#include "ColorImage Alpha1Doc.h"
#include "ColorImage Alpha1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImageAlpha1View

IMPLEMENT_DYNCREATE(CColorImageAlpha1View, CView)

BEGIN_MESSAGE_MAP(CColorImageAlpha1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CColorImageAlpha1View::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CColorImageAlpha1View::OnGrayScale)
	ON_COMMAND(IDM_ADD_IMAGE, &CColorImageAlpha1View::OnAddImage)
	ON_COMMAND(IDM_SUB_IMAGE, &CColorImageAlpha1View::OnSubImage)
	ON_COMMAND(IDM_MUL_IMAGE, &CColorImageAlpha1View::OnMulImage)
	//ON_COMMAND(IDM_DIV_IMAGE, &CColorImageAlpha1View::OnDivImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CColorImageAlpha1View::OnReverseImage)
	ON_COMMAND(IDM_DARK_IMAGE, &CColorImageAlpha1View::OnDarkImage)
	ON_COMMAND(IDM_AND_IMAGE, &CColorImageAlpha1View::OnAndImage)
	ON_COMMAND(IDM_OR_IMAGE, &CColorImageAlpha1View::OnOrImage)
	ON_COMMAND(IDM_XOR_IMAGE, &CColorImageAlpha1View::OnXorImage)
	ON_COMMAND(IDM_ZOOMIN, &CColorImageAlpha1View::OnZoomin)
	ON_COMMAND(IDM_ZOOMIN2, &CColorImageAlpha1View::OnZoomin2)
	ON_COMMAND(IDM_ZOOMOUT, &CColorImageAlpha1View::OnZoomout)
	ON_COMMAND(IDM_ROTATE, &CColorImageAlpha1View::OnRotate)
	ON_COMMAND(IDM_ROTATE2, &CColorImageAlpha1View::OnRotate2)
	ON_COMMAND(IDM_MOVE_IMAGE, &CColorImageAlpha1View::OnMoveImage)
	ON_COMMAND(IDM_ROTATION, &CColorImageAlpha1View::OnRotation)
	ON_COMMAND(IDM_ROTATION2, &CColorImageAlpha1View::OnRotation2)
	ON_COMMAND(IDM_HISTO_STRETCH, &CColorImageAlpha1View::OnHistoStretch)
	ON_COMMAND(IDM_ENDIN, &CColorImageAlpha1View::OnEndin)
	ON_COMMAND(IDM_HISTO_EQUAL, &CColorImageAlpha1View::OnHistoEqual)
	ON_COMMAND(IDM_EMBOSS_RGB, &CColorImageAlpha1View::OnEmbossRgb)
	ON_COMMAND(IDM_EMBOSS_HSI, &CColorImageAlpha1View::OnEmbossHsi)
	ON_COMMAND(IDM_BLURR, &CColorImageAlpha1View::OnBlurr)
	ON_COMMAND(IDM_BLURR2, &CColorImageAlpha1View::OnBlurr2)
	ON_COMMAND(IDM_SMOOT, &CColorImageAlpha1View::OnSmoot)
	ON_COMMAND(IDM_SHARP1, &CColorImageAlpha1View::OnSharp1)
	ON_COMMAND(IDM_SHARP2, &CColorImageAlpha1View::OnSharp2)
	ON_COMMAND(IDM_SHARP3, &CColorImageAlpha1View::OnSharp3)
	ON_COMMAND(IDM_EDGE1, &CColorImageAlpha1View::OnEdge1)
	ON_COMMAND(IDM_EDGE2, &CColorImageAlpha1View::OnEdge2)
	//ON_COMMAND(IDM_EDGE3, &CColorImageAlpha1View::OnEdge3)
	ON_COMMAND(IDM_EDGE4, &CColorImageAlpha1View::OnEdge4)
	ON_COMMAND(IDM_EDGE5, &CColorImageAlpha1View::OnEdge5)
	ON_COMMAND(IDM_EDGE6, &CColorImageAlpha1View::OnEdge6)
	ON_COMMAND(IDM_EDGE7, &CColorImageAlpha1View::OnEdge7)
	ON_COMMAND(IDM_CHANGE_SATUR, &CColorImageAlpha1View::OnChangeSatur)
	ON_COMMAND(IDM_ORANGE, &CColorImageAlpha1View::OnOrange)
END_MESSAGE_MAP()

// CColorImageAlpha1View 생성/소멸

CColorImageAlpha1View::CColorImageAlpha1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImageAlpha1View::~CColorImageAlpha1View()
{
}

BOOL CColorImageAlpha1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImageAlpha1View 그리기

void CColorImageAlpha1View::OnDraw(CDC* pDC)
{
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//int R, G, B;
	//for (int i = 0; i < pDoc->m_inH; i++)
	//	for (int k = 0; k < pDoc->m_inW; k++) {
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
	//	}

	//for (int i = 0; i < pDoc->m_outH; i++)
	//	for (int k = 0; k < pDoc->m_outW; k++) {
	//		R = pDoc->m_outImageR[i][k];
	//		G = pDoc->m_outImageG[i][k];
	//		B = pDoc->m_outImageB[i][k];
	//		pDC->SetPixel(pDoc->m_inW + k + 5 + 5, i + 5, RGB(R, G, B));
	//	}

	
	/////// 더블 버퍼링
	//int i, k;
	//unsigned char R, G, B;
	//// 메모리 DC 선언
	//CDC memDC;
	//CBitmap* pOldBitmap, bitmap;

	//// 화면 DC와 호환되는 메모리 DC 객체를 생성
	//memDC.CreateCompatibleDC(pDC);

	//// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	//bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	//pOldBitmap = memDC.SelectObject(&bitmap);
	//memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	//// 메모리 DC에 그리기
	//for (i = 0; i < pDoc->m_inH; i++) {
	//	for (k = 0; k < pDoc->m_inW; k++) {
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		memDC.SetPixel(k, i, RGB(R, G, B));
	//	}
	//}
	//// 메모리 DC를 화면 DC에 고속 복사
	//pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	//memDC.SelectObject(pOldBitmap);
	//memDC.DeleteDC();
	//bitmap.DeleteObject();

	/////////////////////

	//// 화면 DC와 호환되는 메모리 DC 객체를 생성
	//memDC.CreateCompatibleDC(pDC);

	//// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	//bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	//pOldBitmap = memDC.SelectObject(&bitmap);
	//memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	//// 메모리 DC에 그리기
	//for (i = 0; i < pDoc->m_outH; i++) {
	//	for (k = 0; k < pDoc->m_outW; k++) {
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		memDC.SetPixel(k, i, RGB(R, G, B));
	//	}
	//}
	//// 메모리 DC를 화면 DC에 고속 복사
	//pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	//memDC.SelectObject(pOldBitmap);
	//memDC.DeleteDC();
	//bitmap.DeleteObject();

	//////화면크기 자동 조절
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화




	//출력 영상의 크기를 자동 조절
	double MAXSIZE = 800; //필요시 실 모니터 또는 화면의 해상도의 따라서 변경 가능
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0;   //기본

	if (inH > MAXSIZE || inW > MAXSIZE) {
		//hop을 새로 계산
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);

		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < inH; i++) {
		for (k = 0; k < inW; k++) {
			R = pDoc->m_inImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}




	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화


	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; // 기본

	if (outH > MAXSIZE || outW > MAXSIZE) {
		// hop을 새로 계산.
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < outH; i++) {
		for (k = 0; k < outW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);
	

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

}



// CColorImageAlpha1View 인쇄

BOOL CColorImageAlpha1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImageAlpha1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImageAlpha1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CColorImageAlpha1View 진단

#ifdef _DEBUG
void CColorImageAlpha1View::AssertValid() const
{
	CView::AssertValid();
}

void CColorImageAlpha1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImageAlpha1Doc* CColorImageAlpha1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImageAlpha1Doc)));
	return (CColorImageAlpha1Doc*)m_pDocument;
}
#endif //_DEBUG


// CColorImageAlpha1View 메시지 처리기


void CColorImageAlpha1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);

}


void CColorImageAlpha1View::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScale();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSubImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSubImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnMulImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMulImage();
	Invalidate(TRUE);
}


//void CColorImageAlpha1View::OnDivImage()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CColorImageAlpha1Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//
//	pDoc->OnDivImage();
//	Invalidate(TRUE);
//}


void CColorImageAlpha1View::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnDarkImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDarkImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnZoomin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomin();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnZoomin2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomin2();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomout();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnRotate2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate2();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMoveImage();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnRotation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotation();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnRotation2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotation2();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEndin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndin();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEmbossRgb()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossRgb();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEmbossHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossHsi();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnBlurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnBlurr2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr2();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSmoot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSmoot();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSharp1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharp1();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSharp2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharp2();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnSharp3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharp3();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge1();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEdge2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge2();
	Invalidate(TRUE);
}


//void CColorImageAlpha1View::OnEdge3()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CColorImageAlpha1Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//
//	pDoc->OnEdge3();
//	Invalidate(TRUE);
//}


void CColorImageAlpha1View::OnEdge4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge4();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEdge5()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge5();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEdge6()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge6();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnEdge7()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge7();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnChangeSatur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeSatur();
	Invalidate(TRUE);
}


void CColorImageAlpha1View::OnOrange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageAlpha1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrange();
	Invalidate(TRUE);
}
