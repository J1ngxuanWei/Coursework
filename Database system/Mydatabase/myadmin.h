#pragma once
#include "afxdialogex.h"

#include "winsock.h"
#include "mysql.h"


// myadmin 对话框

class myadmin : public CDialogEx
{
	DECLARE_DYNAMIC(myadmin)

public:
	myadmin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~myadmin();
	MYSQL mq;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl lis1;
	CListCtrl lis2;
	CListCtrl lis3;
	CListCtrl lis4;
	CListCtrl lis5;
	afx_msg void OnBnClickedButton1();
	CEdit bmbh;
	CEdit bmmc;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CEdit ygsfz;
	CEdit ygxm;
	CEdit ygxb;
	CEdit ygbmbh;
	CEdit ygzh;
	CEdit ygmm;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	CEdit spbm;
	CEdit spmc;
	CEdit spkc;
	CEdit spjj;
	CEdit spxsj;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedOk();
};
