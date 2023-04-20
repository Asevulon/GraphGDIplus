// Drawer.cpp: файл реализации
//

#include "pch.h"
#include "GraphGDIplus.h"
#include "Drawer.h"


// Drawer

IMPLEMENT_DYNAMIC(Drawer, CStatic)

Drawer::Drawer()
{
	GdiplusStartup(&token, &si, NULL);
	xPadding = 15;
	yPadding = 11;
}

Drawer::~Drawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(Drawer, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений Drawer




void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics gr(lpDrawItemStruct->hDC);

	int ActualTop(yPadding),
		ActualBottom(lpDrawItemStruct->rcItem.bottom - yPadding),
		ActualLeft(xPadding),
		ActualRight(lpDrawItemStruct->rcItem.right - xPadding);

	Pen BackGroungPen(Color(240, 240, 240));
	float steplenY = (ActualBottom - ActualTop) / 10.;
	for (int i = 0; i < 10; i++)
	{
		gr.DrawLine
	}

	Pen pen(Color::Black);
	gr.DrawLine(&pen, ActualLeft, ActualTop, ActualLeft, ActualBottom);
	gr.DrawLine(&pen, ActualLeft, ActualBottom, ActualRight, ActualBottom);
	

	Matrix matr;
	matr.Translate(ActualLeft, (ActualBottom - ActualTop) / 2.);
	gr.SetTransform(&matr);


	
	
}
