
// MyDlg.h: файл заголовка
//

#pragma once
#include"Drawer.h"
#define TIMER_ELAPSE 25
// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHGDIPLUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Drawer drw;
	afx_msg void OnBnClickedOk();
	CEdit w1Ctrl;
	CEdit w2Ctrl;
	afx_msg void OnBnClickedCheck1();
	bool WasDataInputed;
	CButton StartButtonCtrl;
	CButton CBCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	UINT_PTR TimerId;
	CSliderCtrl SliderCtrl;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
