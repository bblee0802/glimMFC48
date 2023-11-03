#include "pch.h"
#include "StaticImage.h"

CStaticImage::CStaticImage() 
{
	CStatic::CStatic();

	//초기화
	m_nImageWidth = 0;
	m_nImageHeight = 0;
	m_nImagePitch = 0;

	//영역밖으로 초기화 
	m_ptTargetMark.x = -100;
	m_ptTargetMark.y = -100;
	m_nTargetSize = 0;
	m_bDrawTarget = false;
}

CStaticImage::~CStaticImage() {

	DestroyImage();

	CStatic::~CStatic();
}

void CStaticImage::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();

	// Client 영역의 크기의 8bit 이미지 생성
	CRect rc;
	GetClientRect(&rc);
	Create8bitImage(rc.Width(), rc.Height());

	//이미지 초기화
	onClearImage();
}

BEGIN_MESSAGE_MAP(CStaticImage, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CStaticImage::drawImage(CDC *pDC)
{
	//이미지 존재하면 그린다. 
	if (!m_image.IsNull()) {
		m_image.Draw(pDC->m_hDC, 0, 0, m_image.GetWidth(), m_image.GetHeight());
	}
}

void CStaticImage::drawTargetMark(CDC *pDC)
{
	int x = m_ptTargetMark.x;
	int y = m_ptTargetMark.y;
	int r = m_nTargetSize;
	
	CRect rc;
	rc.left = x - r;
	rc.top = y - r;
	rc.right = x + r;
	rc.bottom = y + r;

	POINT linePoints[8] = {
		{x, y-r},
		{x, y},
		{x, y+r},
	    {x, y} ,
	    {x-r, y},
	    {x, y},
	    {x+r,y},
	    {x,y}
	};

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	CPen *pOldPen = pDC->SelectObject(&pen);

	CBrush brush(COLOR_BLACK);
	CBrush *pOldBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(&rc);
	pDC->Polyline(linePoints, 8);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


void CStaticImage::OnPaint()
{
	CPaintDC dc(this); 

	//image
	drawImage(&dc);

	//target mark
	if(m_bDrawTarget)
		drawTargetMark(&dc);
}

void CStaticImage::DestroyImage()
{
	if (!m_image.IsNull()) {
		m_image.Destroy();
		m_nImageWidth = 0;
		m_nImageHeight = 0;
		m_nImagePitch = 0;
	}
}

// 8bit 이미지를 생성한다.
void CStaticImage::Create8bitImage(int nWidth, int nHeight)
{
	//이미 존재하고 있으면 없앤다.  
	DestroyImage();
		 
	if (m_image.Create(nWidth, nHeight, 8)) { //이미지 생성에 성공한 경우 
		m_nImageWidth = m_image.GetWidth();
		m_nImageHeight = m_image.GetHeight();
		m_nImagePitch = m_image.GetPitch();

		RGBQUAD colorTable[256];
		for (int i = 0; i < 256; i++) {
			colorTable[i].rgbRed = \
			colorTable[i].rgbGreen = \
			colorTable[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, colorTable);
	}
}

//(xPos, yPos)에 반지름 nRaudius인 원을 그린다.  
void CStaticImage::onDrawCircel(int xPos, int yPos, int nRadius)
{
	if (m_image.IsNull())
		return;

	unsigned char *fm = (unsigned char *)m_image.GetBits();

	int nDiameterX = xPos + nRadius;
	int nDiameterY = yPos + nRadius;

	//시작점 X 체크
	int x = xPos - nRadius;
	if (x < 0) 	x = 0;
	
	//시작점 Y 체크
	int y = yPos - nRadius;
	if (y < 0) y = 0;

	for (int j = y; j < y + nDiameterY; j++) {
		for (int i = x; i < x + nDiameterX; i++) {
			
			//이미지 범위를 넘어는 체크
			if (j >= m_nImageHeight || i >= m_nImageWidth)
				continue;
		
			if (isInCircle(i, j, xPos, yPos, nRadius)) {
				fm[j*m_nImagePitch + i] = COLOR_MONO_GRAY;
			}
		}
	}

	m_bDrawTarget = false;

	//update CStaticImage
	Invalidate();

}

//이미지를 초기화 한다.
void CStaticImage::onClearImage()
{
	if (m_image.IsNull())
		return;
	
	unsigned char *fm = (unsigned char *)m_image.GetBits();

	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			fm[j*m_nImagePitch + i] = COLOR_MONO_BLACK;
		}
	}
}
//타겟 모양 그리기
void CStaticImage::onDrawTargetMark(DPOINT ptTarget , int nSize)
{
	m_ptTargetMark.x = ptTarget.x;
	m_ptTargetMark.y = ptTarget.y;
	m_nTargetSize = nSize;

	if(ptTarget.x > 0 || ptTarget.y >0)
		m_bDrawTarget = true;

	//redraw
	Invalidate();
}

// (x,y)가 원의 내부에 있으면 true 린턴
bool CStaticImage::isInCircle(int x, int y, int centerX, int centerY, int nRadius)
{
	bool bRet = false;
	
	double dX = x - centerX;
	double dY = y - centerY;
	double dDist = dX * dX + dY * dY;
	
	if (dDist <= nRadius * nRadius)
		bRet = true;

	return bRet;
}

int  CStaticImage::GetImageWidth()
{
	return m_nImageWidth;
}

int  CStaticImage::GetImageHeight()
{
	return m_nImageHeight;
}


//이미지에서 nThreshold 이상의 점들의 무게중심을 구한다.
DPOINT CStaticImage::GetImageCenterGravity(int nThreshold)
{
	DPOINT ptCenter = { 0.0, 0.0 };

	if (m_image.IsNull())
		return ptCenter;

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	unsigned char *fm = (unsigned char *)m_image.GetBits();
	
	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			if (fm[j*m_nImagePitch + i] >= nThreshold) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	
	if (nCount > 0) { //0으로 나누기하는 경우 방지
		ptCenter.x = (double)nSumX / nCount;
		ptCenter.y = (double)nSumY / nCount;
	}

	return ptCenter;
}