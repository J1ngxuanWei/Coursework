// mycg.cpp: 实现文件
//

#include "pch.h"
#include "Mydatabase.h"
#include "afxdialogex.h"
#include "mycg.h"

#include "winsock.h"
#include "mysql.h"


// mycg 对话框

IMPLEMENT_DYNAMIC(mycg, CDialogEx)

mycg::mycg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

mycg::~mycg()
{
}

void mycg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC8, sfz);
	DDX_Control(pDX, IDC_STATIC9, zh);
	DDX_Control(pDX, IDC_STATIC10, sj);
	DDX_Control(pDX, IDC_LIST1, liss);
	DDX_Control(pDX, IDC_EDIT1, bm);
	DDX_Control(pDX, IDC_EDIT2, sl);
}


BEGIN_MESSAGE_MAP(mycg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &mycg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &mycg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// mycg 消息处理程序


BOOL mycg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 5000, NULL);
	mysql_init(&mq);
	mysql_real_connect(&mq, "localhost", "root", "wjx20021002", "supermarket", 3306, NULL, 0);
	mysql_query(&mq, "set names 'gb2312'");

	liss.InsertColumn(0, "商品编码", LVCFMT_LEFT, 100);
	liss.InsertColumn(1,"身份证号码" , LVCFMT_LEFT, 180);
	liss.InsertColumn(2, "入库数量", LVCFMT_LEFT, 100);
	liss.InsertColumn(3, "入库时间", LVCFMT_LEFT, 218);

	liss.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	liss.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	liss.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏

	liss.Update(0);

	CString se;
	se.Format("SELECT * FROM 采购、入库 ;");
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	for (int i = 0; i < res->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		int itemIndex = liss.InsertItem(0, _T("")); // 插入新行
		liss.SetItemText(itemIndex, 0, row[0]);
		liss.SetItemText(itemIndex, 1, row[1]);
		liss.SetItemText(itemIndex, 2, row[2]);
		liss.SetItemText(itemIndex, 3, row[3]);
		liss.Update(itemIndex);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void mycg::setinf(CString n)
{
	CString zhh = "个人账号：" + n;
	zh.SetWindowTextA(zhh);
	CString se;
	se.Format("SELECT 身份证号码 FROM 员工 WHERE 账号='%s';", n);
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	MYSQL_ROW row = mysql_fetch_row(res);
	CString p = row[0];
	sfzh = p;
	p = "身份证号后6位：" + p.Mid(12, 6);
	sfz.SetWindowTextA(p);
	CString str; //获取系统时间 　　
	CTime tm;
	tm = CTime::GetCurrentTime();
	str = tm.Format("%Y年%m月%d日 %X");
	sj.SetWindowTextA(str);
}


void mycg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sti; //获取系统时间 　　
	CTime tm;
	tm = CTime::GetCurrentTime();
	sti = tm.Format("%Y年%m月%d日 %X");

	CString ins;
	CString bmm;
	CString sll;
	bm.GetWindowTextA(bmm);
	sl.GetWindowTextA(sll);

	if (bmm == "" || sll == "")
	{
		MessageBox("输入项不能为空！");
		return;
	}

	//执行数据更新
	ins.Format("call adjpronub('%s','%s');", bmm, sll);
	bool isf = mysql_query(&mq, ins);
	if (isf)
	{
		MessageBox("输入数据不合法导致同步数据错误，请重新输入后重复该操作！");
		return;
	}
	ins.Format("insert into 采购、入库 values ('%s','%s','%s','%s');", bmm, sfzh, sll, sti);
	mysql_query(&mq, ins);
	MessageBox("成功");
	//
	CString se;
	se.Format("SELECT * FROM 采购、入库 WHERE 入库时间='%s';", sti);
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	MYSQL_ROW row = mysql_fetch_row(res);

	// 设置每列的文本
	int itemIndex = liss.InsertItem(0, _T("")); // 插入新行
	liss.SetItemText(itemIndex, 0, row[0]);
	liss.SetItemText(itemIndex, 1, row[1]);
	liss.SetItemText(itemIndex, 2, row[2]);
	liss.SetItemText(itemIndex, 3, row[3]);
	liss.Update(itemIndex);

}


void mycg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void mycg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	liss.DeleteAllItems();
	CString se;
	se.Format("SELECT * FROM 采购、入库 ;");
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	for (int i = 0; i < res->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		int itemIndex = liss.InsertItem(0, _T("")); // 插入新行
		liss.SetItemText(itemIndex, 0, row[0]);
		liss.SetItemText(itemIndex, 1, row[1]);
		liss.SetItemText(itemIndex, 2, row[2]);
		liss.SetItemText(itemIndex, 3, row[3]);
		liss.Update(itemIndex);
	}

	CDialogEx::OnTimer(nIDEvent);
}
