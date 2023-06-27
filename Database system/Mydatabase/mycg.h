#pragma once
#include "afxdialogex.h"

#include "winsock.h"
#include "mysql.h"


// mycg 对话框

class mycg : public CDialogEx
{
	DECLARE_DYNAMIC(mycg)

public:
	mycg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mycg();
	MYSQL mq;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void setinf(CString n);
	CStatic sfz;
	CString sfzh;
	CStatic zh;
	CStatic sj;
	afx_msg void OnBnClickedButton1();
	CListCtrl liss;
	CEdit bm;
	CEdit sl;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
