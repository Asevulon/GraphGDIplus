#pragma once


// Drawer
#include<gdiplus.h>
using namespace Gdiplus;

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


	int xPadding;
	int yPadding;
};


