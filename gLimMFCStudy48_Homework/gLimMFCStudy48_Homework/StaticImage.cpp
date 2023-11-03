#include "pch.h"
#include "StaticImage.h"

CStaticImage::CStaticImage() 
{
	CStatic::CStatic();

	//�ʱ�ȭ
	m_nImageWidth = 0;
	m_nImageHeight = 0;
	m_nImagePitch = 0;

	//���������� �ʱ�ȭ 
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

	// Client ������ ũ���� 8bit �̹��� ����
	CRect rc;
	GetClientRect(&rc);
	Create8bitImage(rc.Width(), rc.Height());

	//�̹��� �ʱ�ȭ
	onClearImage();
}

BEGIN_MESSAGE_MAP(CStaticImage, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CStaticImage::drawImage(CDC *pDC)
{
	//�̹��� �����ϸ� �׸���. 
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

// 8bit �̹����� �����Ѵ�.
void CStaticImage::Create8bitImage(int nWidth, int nHeight)
{
	//�̹� �����ϰ� ������ ���ش�.  
	DestroyImage();
		 
	if (m_image.Create(nWidth, nHeight, 8)) { //�̹��� ������ ������ ��� 
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

//(xPos, yPos)�� ������ nRaudius�� ���� �׸���.  
void CStaticImage::onDrawCircel(int xPos, int yPos, int nRadius)
{
	if (m_image.IsNull())
		return;

	unsigned char *fm = (unsigned char *)m_image.GetBits();

	int nDiameterX = xPos + nRadius;
	int nDiameterY = yPos + nRadius;

	//������ X üũ
	int x = xPos - nRadius;
	if (x < 0) 	x = 0;
	
	//������ Y üũ
	int y = yPos - nRadius;
	if (y < 0) y = 0;

	for (int j = y; j < y + nDiameterY; j++) {
		for (int i = x; i < x + nDiameterX; i++) {
			
			//�̹��� ������ �Ѿ�� üũ
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

//�̹����� �ʱ�ȭ �Ѵ�.
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
//Ÿ�� ��� �׸���
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

// (x,y)�� ���� ���ο� ������ true ����
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


//�̹������� nThreshold �̻��� ������ �����߽��� ���Ѵ�.
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
	
	if (nCount > 0) { //0���� �������ϴ� ��� ����
		ptCenter.x = (double)nSumX / nCount;
		ptCenter.y = (double)nSumY / nCount;
	}

	return ptCenter;
}