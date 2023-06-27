
// MydatabaseDlg.h: 头文件
//

#pragma once

#include "winsock.h"
#include "mysql.h"


// CMydatabaseDlg 对话框
class CMydatabaseDlg : public CDialogEx
{
// 构造
public:
	CMydatabaseDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYDATABASE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CFont myf;
	CFont myf2;
	CFont myf3;
	CFont myf4;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MYSQL mq;
	CStatic mtext;
	CStatic mtext2;
	CStatic mtext3;
	CStatic mtext4;
	afx_msg void OnBnClickedOk();
	CEdit t1;
	CEdit t2;
	afx_msg void OnBnClickedCancel();
};
