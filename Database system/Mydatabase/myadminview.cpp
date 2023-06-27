// myadminview.cpp: 实现文件
//

#include "pch.h"
#include "Mydatabase.h"
#include "afxdialogex.h"
#include "myadminview.h"

#include "myadmin.h"


// myadminview 对话框

IMPLEMENT_DYNAMIC(myadminview, CDialogEx)

myadminview::myadminview(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

myadminview::~myadminview()
{
}

void myadminview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lis1);
	DDX_Control(pDX, IDC_LIST2, lis2);
}


BEGIN_MESSAGE_MAP(myadminview, CDialogEx)
	ON_BN_CLICKED(IDOK, &myadminview::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &myadminview::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// myadminview 消息处理程序


void myadminview::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	myadmin* pDlg = new myadmin;
	pDlg->Create(IDD_DIALOG3, this);    //创建对话框
	pDlg->CenterWindow();
	pDlg->ShowWindow(SW_SHOW);    //显示对话框
}


void myadminview::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


BOOL myadminview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 5000, NULL);

	mysql_init(&mq);
	mysql_real_connect(&mq, "localhost", "root", "wjx20021002", "supermarket", 3306, NULL, 0);
	mysql_query(&mq, "set names 'gb2312'");

	lis1.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis1.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏


	lis2.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis2.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏

	//1
	lis1.InsertColumn(0, "身份证号码", LVCFMT_LEFT, 140);
	lis1.InsertColumn(1, "姓名", LVCFMT_LEFT, 60);
	lis1.InsertColumn(2, "性别", LVCFMT_LEFT, 45);
	lis1.InsertColumn(3, "部门编号", LVCFMT_LEFT, 80);
	lis1.InsertColumn(4, "商品编码", LVCFMT_LEFT, 80);
	lis1.InsertColumn(5, "销售商品", LVCFMT_LEFT, 80);
	lis1.InsertColumn(6, "销售数量", LVCFMT_LEFT, 80);
	lis1.InsertColumn(7, "库存数量", LVCFMT_LEFT, 80);
	lis1.InsertColumn(8, "销售时间", LVCFMT_LEFT, 200);
	lis1.Update(0);

	CString se1;
	se1.Format("SELECT * FROM 销售记录;");
	mysql_query(&mq, se1);
	MYSQL_RES* res1 = mysql_store_result(&mq);
	for (int i = 0; i < res1->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res1);
		int itemIndex = lis1.InsertItem(0, _T("")); // 插入新行
		lis1.SetItemText(itemIndex, 0, row[0]);
		lis1.SetItemText(itemIndex, 1, row[1]);
		lis1.SetItemText(itemIndex, 2, row[2]);
		lis1.SetItemText(itemIndex, 3, row[3]);
		lis1.SetItemText(itemIndex, 4, row[4]);
		lis1.SetItemText(itemIndex, 5, row[5]);
		lis1.SetItemText(itemIndex, 6, row[6]);
		lis1.SetItemText(itemIndex, 7, row[7]);
		lis1.SetItemText(itemIndex, 8, row[8]);
		lis1.Update(itemIndex);
	}

	//2
	lis2.InsertColumn(0, "身份证号码", LVCFMT_LEFT, 140);
	lis2.InsertColumn(1, "姓名", LVCFMT_LEFT, 60);
	lis2.InsertColumn(2, "性别", LVCFMT_LEFT, 45);
	lis2.InsertColumn(3, "部门编号", LVCFMT_LEFT, 80);
	lis2.InsertColumn(4, "商品编码", LVCFMT_LEFT, 80);
	lis2.InsertColumn(5, "名称", LVCFMT_LEFT, 80);
	lis2.InsertColumn(6, "入库数量", LVCFMT_LEFT, 80);
	lis2.InsertColumn(7, "库存数量", LVCFMT_LEFT, 80);
	lis2.InsertColumn(8, "入库时间", LVCFMT_LEFT, 200);
	lis2.Update(0);

	CString se2;
	se2.Format("SELECT * FROM 采购记录;");
	mysql_query(&mq, se2);
	MYSQL_RES* res2 = mysql_store_result(&mq);
	for (int i = 0; i < res2->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res2);
		int itemIndex = lis2.InsertItem(0, _T("")); // 插入新行
		lis2.SetItemText(itemIndex, 0, row[0]);
		lis2.SetItemText(itemIndex, 1, row[1]);
		lis2.SetItemText(itemIndex, 2, row[2]);
		lis2.SetItemText(itemIndex, 3, row[3]);
		lis2.SetItemText(itemIndex, 4, row[4]);
		lis2.SetItemText(itemIndex, 5, row[5]);
		lis2.SetItemText(itemIndex, 6, row[6]);
		lis2.SetItemText(itemIndex, 7, row[7]);
		lis2.SetItemText(itemIndex, 8, row[8]);
		lis2.Update(itemIndex);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void myadminview::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lis1.DeleteAllItems();
	lis2.DeleteAllItems();
	CString se1;
	se1.Format("SELECT * FROM 销售记录;");
	mysql_query(&mq, se1);
	MYSQL_RES* res1 = mysql_store_result(&mq);
	for (int i = 0; i < res1->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res1);
		int itemIndex = lis1.InsertItem(0, _T("")); // 插入新行
		lis1.SetItemText(itemIndex, 0, row[0]);
		lis1.SetItemText(itemIndex, 1, row[1]);
		lis1.SetItemText(itemIndex, 2, row[2]);
		lis1.SetItemText(itemIndex, 3, row[3]);
		lis1.SetItemText(itemIndex, 4, row[4]);
		lis1.SetItemText(itemIndex, 5, row[5]);
		lis1.SetItemText(itemIndex, 6, row[6]);
		lis1.SetItemText(itemIndex, 7, row[7]);
		lis1.SetItemText(itemIndex, 8, row[8]);
		lis1.Update(itemIndex);
	}
	CString se2;
	se2.Format("SELECT * FROM 采购记录;");
	mysql_query(&mq, se2);
	MYSQL_RES* res2 = mysql_store_result(&mq);
	for (int i = 0; i < res2->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res2);
		int itemIndex = lis2.InsertItem(0, _T("")); // 插入新行
		lis2.SetItemText(itemIndex, 0, row[0]);
		lis2.SetItemText(itemIndex, 1, row[1]);
		lis2.SetItemText(itemIndex, 2, row[2]);
		lis2.SetItemText(itemIndex, 3, row[3]);
		lis2.SetItemText(itemIndex, 4, row[4]);
		lis2.SetItemText(itemIndex, 5, row[5]);
		lis2.SetItemText(itemIndex, 6, row[6]);
		lis2.SetItemText(itemIndex, 7, row[7]);
		lis2.SetItemText(itemIndex, 8, row[8]);
		lis2.Update(itemIndex);
	}
	CDialogEx::OnTimer(nIDEvent);
}
