#pragma once
#include <afxwin.h>


#define COLOR_MONO_BLACK    0x00
#define COLOR_MONO_GRAY		0x80 
#define COLOR_YELLOW		RGB(255, 255, 0)
#define COLOR_BLACK         RGB(0,0,0)

//double point ¼±¾ð
typedef struct _DPOINT_ {
	double x;
	double y;
}DPOINT ;

class CStaticImage : public CStatic
{
	virtual void PreSubclassWindow();
public:
	CStaticImage();
	~CStaticImage();
public:
	CImage m_image;
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nImagePitch;
	
	//target mark
	POINT m_ptTargetMark;
	int m_nTargetSize;
	bool m_bDrawTarget;

public:
	void drawImage(CDC *pDC);
	void drawTargetMark(CDC *pDC);
	void DestroyImage();
	void Create8bitImage(int nWidth, int nHeight);
	void onDrawCircel(int xPos, int yPos, int nRadius);
	void onClearImage();
	void onDrawTargetMark(DPOINT ptTarget, int nSize);
	bool isInCircle(int x, int y, int centerX, int centerY, int nRadius);
	int  GetImageWidth();
	int  GetImageHeight();
	DPOINT GetImageCenterGravity(int nThreshold = COLOR_MONO_GRAY);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

