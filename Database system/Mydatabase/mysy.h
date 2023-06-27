#pragma once
#include "afxdialogex.h"

#include "winsock.h"
#include "mysql.h"


// mysy 对话框

class mysy : public CDialogEx
{
	DECLARE_DYNAMIC(mysy)

public:
	mysy(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mysy();
	MYSQL mq;
	CString sfzh;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void setinf(CString n);
	CStatic sfz;
	CStatic zh;
	CStatic sj;
	afx_msg void OnBnClickedButton1();
	CEdit mc;
	CEdit bh;
	CEdit sl;
	CListCtrl lis;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
