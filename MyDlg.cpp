
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "GraphGDIplus.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHGDIPLUS_DIALOG, pParent)
	, WasDataInputed(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, drw);
	DDX_Control(pDX, IDC_EDIT1, w1Ctrl);
	DDX_Control(pDX, IDC_EDIT2, w2Ctrl);
	DDX_Control(pDX, IDOK, StartButtonCtrl);
	DDX_Control(pDX, IDC_CHECK1, CBCtrl);
	DDX_Control(pDX, IDC_SLIDER1, SliderCtrl);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &MyDlg::OnBnClickedCheck1)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	w1Ctrl.SetWindowTextW(L"1000");
	w2Ctrl.SetWindowTextW(L"2");

	CBCtrl.EnableWindow(FALSE);

	SliderCtrl.SetRange(1, 400);
	SliderCtrl.SetTicFreq(1);
	SliderCtrl.SetPos(100);
	SliderCtrl.EnableWindow(FALSE);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnBnClickedOk()
{
	wchar_t str[15];
	w1Ctrl.GetWindowTextW(str, w1Ctrl.GetWindowTextLengthW() + 1);
	drw.w1 = wcstold(str, NULL);
	w2Ctrl.GetWindowTextW(str, w2Ctrl.GetWindowTextLengthW() + 1);
	drw.w2 = drw.w1 + wcstold(str, NULL);
	drw.y = 0;
	drw.Invalidate(FALSE);
	WasDataInputed = true;
	CBCtrl.EnableWindow(TRUE);

}


void MyDlg::OnBnClickedCheck1()
{
	if (!WasDataInputed)return;
	int val = CBCtrl.GetCheck();
	if (val == BST_CHECKED)
	{
		SliderCtrl.EnableWindow(TRUE);
		w1Ctrl.EnableWindow(FALSE);
		w2Ctrl.EnableWindow(FALSE);
		StartButtonCtrl.EnableWindow(FALSE);
		TimerId = SetTimer(1, TIMER_ELAPSE, NULL);
	}
	else
	{
		SliderCtrl.EnableWindow(FALSE);
		w1Ctrl.EnableWindow(TRUE);
		w2Ctrl.EnableWindow(TRUE);
		StartButtonCtrl.EnableWindow(TRUE);
		KillTimer(TimerId);
	}
}


void MyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	float dy = fabs(log10(drw.right) / log10(NUMS_AMOUNT - 1));
	dy *= SliderCtrl.GetPos() / 100.;
	drw.y += dy;
	drw.Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void MyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
