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
	top = 2;
	bottom = -2;
	left = 0;
	right = 0;
	w1 = -1;
	w2 = -1;
	y = 0;
}

Drawer::~Drawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(Drawer, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений Drawer


const double pi = 4 * atan(1);

void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	Bitmap bm(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top);
	Graphics gr(&bm);
	gr.Clear(Color::White);
	Graphics RealDrawer(lpDrawItemStruct->hDC);
	if (w1 <= 0)
	{
		RealDrawer.DrawImage(&bm, 0, 0);
		return;
	}
	if (w2 <= 0)
	{
		RealDrawer.DrawImage(&bm, 0, 0);
		return;
	}

	gr.SetSmoothingMode(SmoothingModeAntiAlias);

	right = 4 * pi / (w2 - w1);
	xPadding = (right - left) / 9.;
	yPadding = (top - bottom) / 9.;

	float ActualTop = top + yPadding;
	float ActualBottom = bottom - yPadding;
	float ActualLeft = left - xPadding;
	float ActualRight = right + xPadding;

	

	Matrix matr;
	float xScale = float(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) / (ActualRight - ActualLeft);
	float yScale = float(lpDrawItemStruct->rcItem.top - lpDrawItemStruct->rcItem.bottom) / (ActualTop - ActualBottom);
	matr.Scale(xScale, yScale);
	matr.Translate(xPadding, -(ActualTop - ActualBottom) / 2.);


	Pen BackGroundPen(Color(240, 240, 240));
	float steplenY = (top - bottom) / 10.;
	float steplenX = (right - left) / 10.;

	FontFamily FF(L"Arial");
	Gdiplus::Font font(&FF, 12, FontStyle::FontStyleRegular, UnitPixel);
	SolidBrush brush(Color::Black);
	for (int i = 0; i < 11; i++)
	{
		PointF p1, p2;
		p1.X = left;
		p1.Y = top - i * steplenY;

		p2.X = right;
		p2.Y = top - i * steplenY;

		matr.TransformPoints(&p1);
		matr.TransformPoints(&p2);

		gr.DrawLine(&BackGroundPen, p1, p2);


		p1.X = right - i * steplenX;
		p1.Y = top;

		p2.X = right - i * steplenX;
		p2.Y = bottom;

		matr.TransformPoints(&p1);
		matr.TransformPoints(&p2);

		gr.DrawLine(&BackGroundPen, p1, p2);


		CString str;
		str.Format(L"%.2f", top - i * steplenY);

		PointF strPoint(ActualLeft + steplenX / 4., top - (i - 0.125) * steplenY);
		matr.TransformPoints(&strPoint);
		gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);

		str.Format(L"%.2f", right - i * steplenX);

		strPoint.X = right - (i + 0.25) * steplenX;
		strPoint.Y = bottom - steplenY / 2.;
		matr.TransformPoints(&strPoint);
		gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);
	}

	Pen pen(Color::Black, 1.1F);
	PointF p1(left, top), p2(left, bottom);
	matr.TransformPoints(&p1);
	matr.TransformPoints(&p2);
	gr.DrawLine(&pen, p1, p2);

	p1 = PointF(left, bottom);
	p2 = PointF(right, bottom);
	matr.TransformPoints(&p1);
	matr.TransformPoints(&p2);
	gr.DrawLine(&pen, p1, p2);

	p1 = PointF(left, 2);
	matr.TransformPoints(&p1);
	
	Pen DataPen(Color(200, 100, 0));
	steplenX = float(right - left) / float(NUMS_AMOUNT - 1);
	for (int i = 1; i < NUMS_AMOUNT; i++)
	{
		p2 = PointF(i * steplenX, cos(w1 * i * steplenX + y) + cos(w2 * i * steplenY));
		matr.TransformPoints(&p2);
		gr.DrawLine(&DataPen, p1, p2);
		p1 = p2;
	}

	
	RealDrawer.DrawImage(&bm, 0, 0);
}
