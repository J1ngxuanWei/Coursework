// mysy.cpp: 实现文件
//

#include "pch.h"
#include "Mydatabase.h"
#include "afxdialogex.h"
#include "mysy.h"

#include "winsock.h"
#include "mysql.h"


// mysy 对话框

IMPLEMENT_DYNAMIC(mysy, CDialogEx)

mysy::mysy(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

mysy::~mysy()
{
}

void mysy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC5, sfz);
	DDX_Control(pDX, IDC_STATIC6, zh);
	DDX_Control(pDX, IDC_STATIC7, sj);
	DDX_Control(pDX, IDC_EDIT2, mc);
	DDX_Control(pDX, IDC_EDIT1, bh);
	DDX_Control(pDX, IDC_EDIT3, sl);
	DDX_Control(pDX, IDC_LIST2, lis);
}


BEGIN_MESSAGE_MAP(mysy, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &mysy::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &mysy::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// mysy 消息处理程序


BOOL mysy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 5000, NULL);
	mysql_init(&mq);
	mysql_real_connect(&mq, "localhost", "root", "wjx20021002", "supermarket", 3306, NULL, 0);
	mysql_query(&mq, "set names 'gb2312'");

	lis.InsertColumn(0, "身份证号码", LVCFMT_LEFT,167);
	lis.InsertColumn(1, "商品编码", LVCFMT_LEFT,90);
	lis.InsertColumn(2, "销售时间",LVCFMT_LEFT,200);
	lis.InsertColumn(3, "销售商品", LVCFMT_LEFT, 100);
	lis.InsertColumn(4, "数量", LVCFMT_LEFT, 50);

	lis.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏

	lis.Update(0);

	CString se;
	se.Format("SELECT * FROM 销售 ;");
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	for (int i = 0; i < res->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		int itemIndex = lis.InsertItem(0, _T("")); // 插入新行
		lis.SetItemText(itemIndex, 0, row[0]);
		lis.SetItemText(itemIndex, 1, row[1]);
		lis.SetItemText(itemIndex, 2, row[2]);
		lis.SetItemText(itemIndex, 3, row[3]);
		lis.SetItemText(itemIndex, 4, row[4]);
		lis.Update(itemIndex);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void mysy::setinf(CString n)
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
	p = "身份证号后6位：" +p.Mid(12,6);
	sfz.SetWindowTextA(p);
	CString str; //获取系统时间 　　
	CTime tm; 
	tm = CTime::GetCurrentTime();
	str = tm.Format("%Y年%m月%d日 %X");
	sj.SetWindowTextA(str);
}


void mysy::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sti; //获取系统时间 　　
	CTime tm;
	tm = CTime::GetCurrentTime();
	sti = tm.Format("%Y年%m月%d日 %X");

	CString ins;
	CString bm;
	CString mcc;
	CString sll;
	bh.GetWindowTextA(bm);
	mc.GetWindowTextA(mcc);
	sl.GetWindowTextA(sll);

	if (bm == "" || mcc == "" || sll == "")
	{
		MessageBox("输入项不能为空！");
		return;
	}

	ins.Format("insert into 销售 values ('%s','%s','%s','%s','%s');", sfzh, bm, sti, mcc, sll);
	mysql_query(&mq, ins);
	
	//
	CString se;
	se.Format("SELECT * FROM 销售 WHERE 销售时间='%s';", sti);
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	MYSQL_ROW row = mysql_fetch_row(res);
	
	if (row==nullptr)
	{
		MessageBox("库存数量异常，执行销售操作失败，请联系管理员！");
		return;
	}
	else
	{
		MessageBox("成功");
	}

	CString slll = sll;
	int nub = atoi(slll);
	nub = -nub;
	slll.Format("%d", nub);
	ins.Format("call adjpronub('%s','%s');", bm, slll);
	bool isf = mysql_query(&mq, ins);
	if (isf)
	{
		MessageBox("输入数据不合法导致同步数据错误，请重新输入后重复该操作！");
		return;
	}


	// 设置每列的文本
	int itemIndex = lis.InsertItem(0, _T("")); // 插入新行
	lis.SetItemText(itemIndex, 0, row[0]);
	lis.SetItemText(itemIndex, 1, row[1]);
	lis.SetItemText(itemIndex, 2, row[2]);
	lis.SetItemText(itemIndex, 3, row[3]);
	lis.SetItemText(itemIndex, 4, row[4]);
	lis.Update(itemIndex);
}


void mysy::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void mysy::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lis.DeleteAllItems();
	CString se;
	se.Format("SELECT * FROM 销售 ;");
	mysql_query(&mq, se);
	MYSQL_RES* res = mysql_store_result(&mq);
	for (int i = 0; i < res->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		int itemIndex = lis.InsertItem(0, _T("")); // 插入新行
		lis.SetItemText(itemIndex, 0, row[0]);
		lis.SetItemText(itemIndex, 1, row[1]);
		lis.SetItemText(itemIndex, 2, row[2]);
		lis.SetItemText(itemIndex, 3, row[3]);
		lis.SetItemText(itemIndex, 4, row[4]);
		lis.Update(itemIndex);
	}
	CDialogEx::OnTimer(nIDEvent);
}
