
// ColorImage Alpha1Doc.h: CColorImageAlpha1Doc 클래스의 인터페이스
//


#pragma once


class CColorImageAlpha1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageAlpha1Doc() noexcept;
	DECLARE_DYNCREATE(CColorImageAlpha1Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageAlpha1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:

	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char** OnMalloc2D(int h, int w);
	void OnFree2D(unsigned char** memory, int h);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnFreeOutImage();
	void OnGrayScale();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnAddImage();
	void OnSubImage();
	void OnMulImage();
	void OnDivImage();
	void OnReverseImage();
	void OnDarkImage();
	void OnAndImage();
	void OnOrImage();
	void OnXorImage();
	void OnZoomin();
	void OnZoomin2();
	void OnZoomout();
	void OnRotate();
	void OnRotate2();
	void OnMoveImage();
	void OnRotation();
	void OnRotation2();
	void OnHistoStretch();
	void OnEndin();
	void OnHistoEqual();
	void OnEmbossRgb();
	double** OnMalloc2D_Double(int h, int w);
	int OnFree2D_double();
	void OnFree2d_double(double** memory, int h);
	void OnEmbossHsi();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnBlurr();
	void OnBlurr2();
	void OnSmoot();
	void OnSharp1();
	void OnSharp2();
	void OnSharp3();
	void OnEdge1();
	void OnEdge2();
	int OnEdge3();
	void OnEdge4();
	void OnEdge5();
	void OnEdge6();
	void OnEdge7();
	void OnChangeSatur();
	void OnOrange();
};
