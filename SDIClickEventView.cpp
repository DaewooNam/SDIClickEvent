
// SDIClickEventView.cpp: CSDIClickEventView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDIClickEvent.h"
#endif

#include "SDIClickEventDoc.h"
#include "SDIClickEventView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIClickEventView

IMPLEMENT_DYNCREATE(CSDIClickEventView, CView)

BEGIN_MESSAGE_MAP(CSDIClickEventView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIClickEventView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSDIClickEventView 생성/소멸

CSDIClickEventView::CSDIClickEventView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSDIClickEventView::~CSDIClickEventView()
{
}

BOOL CSDIClickEventView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIClickEventView 그리기

bool CSDIClickEventView::IsNotCollsion(CRect rc, CPoint mousePt)
{
	
	if (rc.left > mousePt.x)		return true;
	if (rc.right < mousePt.x)		return true;
	if (rc.top > mousePt.y)			return true;
	if (rc.bottom < mousePt.y)		return true;

		
	return false;
}

void CSDIClickEventView::OnDraw(CDC* pDC)
{
	CSDIClickEventDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	for (list<CRect>::iterator itor = m_listRects.begin(); itor != m_listRects.end(); itor++)
	{
		CRect rc = (*itor);
		pDC->Rectangle(rc);

	} // list 를 통해 사각형 무한대 그리기

	CString str;
	int nCnt = (int)m_listRects.size();
	str.Format("RectCnt: %d", nCnt);
	pDC->TextOut(10,10,str);



}


// CSDIClickEventView 인쇄


void CSDIClickEventView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIClickEventView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIClickEventView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIClickEventView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSDIClickEventView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);

	for (list<CRect>::iterator itor = m_listRects.begin(); itor != m_listRects.end();)
	{

		CRect rc = *itor;


		if (IsNotCollsion(rc, point)==false)
		{
			itor = m_listRects.erase(itor); // 질문 
			break;
		}
		else
		{
			++itor;
		}

	}

	Invalidate();
}

void CSDIClickEventView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSDIClickEventView 진단

#ifdef _DEBUG
void CSDIClickEventView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIClickEventView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIClickEventDoc* CSDIClickEventView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIClickEventDoc)));
	return (CSDIClickEventDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIClickEventView 메시지 처리기


void CSDIClickEventView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rc;

	rc.left = point.x - 50;
	rc.top = point.y - 50;
	rc.right = rc.left + 100;
	rc.bottom = rc.top + 100;

	m_listRects.push_back(rc);
	Invalidate(); 



	CView::OnLButtonDown(nFlags, point);
}
