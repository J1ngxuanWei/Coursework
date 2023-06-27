#pragma once
#include "afxdialogex.h"

#include "winsock.h"
#include "mysql.h"
// myadminview 对话框

class myadminview : public CDialogEx
{
	DECLARE_DYNAMIC(myadminview)

public:
	myadminview(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~myadminview();
	MYSQL mq;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrl lis1;
	CListCtrl lis2;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
