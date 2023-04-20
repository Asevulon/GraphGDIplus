
// GraphGDIplus.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CGraphGDIplusApp:
// Сведения о реализации этого класса: GraphGDIplus.cpp
//

class CGraphGDIplusApp : public CWinApp
{
public:
	CGraphGDIplusApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CGraphGDIplusApp theApp;
