#pragma once


// Drawer
#include<gdiplus.h>
using namespace Gdiplus;

#define NUMS_AMOUNT 500

class Drawer : public CStatic
{
	DECLARE_DYNAMIC(Drawer)

public:
	Drawer();
	virtual ~Drawer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

	ULONG_PTR token;
	GdiplusStartupInput si;

	float w1;
	float w2;

	float top;
	float bottom;
	float left;
	float right;

	float xPadding;
	float yPadding;
	float y;
};


