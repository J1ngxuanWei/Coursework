// myadmin.cpp: 实现文件
//

#include "pch.h"
#include "Mydatabase.h"
#include "afxdialogex.h"
#include "myadmin.h"

#include "winsock.h"
#include "mysql.h"


// myadmin 对话框

IMPLEMENT_DYNAMIC(myadmin, CDialogEx)

myadmin::myadmin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

myadmin::~myadmin()
{
}

void myadmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, lis1);
	DDX_Control(pDX, IDC_LIST2, lis2);
	DDX_Control(pDX, IDC_LIST3, lis3);
	DDX_Control(pDX, IDC_LIST4, lis4);
	DDX_Control(pDX, IDC_LIST5, lis5);
	DDX_Control(pDX, IDC_EDIT1, bmbh);
	DDX_Control(pDX, IDC_EDIT2, bmmc);
	DDX_Control(pDX, IDC_EDIT4, ygsfz);
	DDX_Control(pDX, IDC_EDIT5, ygxm);
	DDX_Control(pDX, IDC_EDIT6, ygxb);
	DDX_Control(pDX, IDC_EDIT3, ygbmbh);
	DDX_Control(pDX, IDC_EDIT7, ygzh);
	DDX_Control(pDX, IDC_EDIT8, ygmm);
	DDX_Control(pDX, IDC_EDIT13, spbm);
	DDX_Control(pDX, IDC_EDIT9, spmc);
	DDX_Control(pDX, IDC_EDIT10, spkc);
	DDX_Control(pDX, IDC_EDIT12, spjj);
	DDX_Control(pDX, IDC_EDIT11, spxsj);
}


BEGIN_MESSAGE_MAP(myadmin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &myadmin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &myadmin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &myadmin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &myadmin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &myadmin::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &myadmin::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &myadmin::OnBnClickedButton7)
	ON_BN_CLICKED(IDOK, &myadmin::OnBnClickedOk)
END_MESSAGE_MAP()


// myadmin 消息处理程序


BOOL myadmin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mysql_init(&mq);
	mysql_real_connect(&mq, "localhost", "root", "wjx20021002", "supermarket", 3306, NULL, 0);
	mysql_query(&mq, "set names 'gb2312'");

	lis1.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis1.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏
	

	lis2.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis2.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏
	

	lis3.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis3.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis3.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏


	lis4.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis4.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis4.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏


	lis5.ModifyStyle(LVS_SHOWSELALWAYS, LVS_REPORT);
	lis5.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lis5.GetHeaderCtrl()->ShowWindow(SW_HIDE); // 隐藏标题栏


	//1
	lis1.InsertColumn(0, "部门编号", LVCFMT_LEFT, 200);
	lis1.InsertColumn(1, "部门名称", LVCFMT_LEFT, 298);
	lis1.Update(0);

	CString se1;
	se1.Format("SELECT * FROM 部门;");
	mysql_query(&mq, se1);
	MYSQL_RES* res1 = mysql_store_result(&mq);
	for (int i = 0; i < res1->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res1);
		int itemIndex = lis1.InsertItem(0, _T("")); // 插入新行
		lis1.SetItemText(itemIndex, 0, row[0]);
		lis1.SetItemText(itemIndex, 1, row[1]);
		lis1.Update(itemIndex);
	}

	//2
	lis2.InsertColumn(0, "身份证号码", LVCFMT_LEFT, 150);
	lis2.InsertColumn(1, "部门编号", LVCFMT_LEFT, 75);
	lis2.InsertColumn(2, "姓名", LVCFMT_LEFT, 50);
	lis2.InsertColumn(3, "性别", LVCFMT_LEFT, 50);
	lis2.InsertColumn(4, "账号", LVCFMT_LEFT, 77);
	lis2.InsertColumn(5, "密码", LVCFMT_LEFT, 76);
	lis2.Update(0);

	CString se2;
	se2.Format("SELECT * FROM 员工;");
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
		lis2.Update(itemIndex);
	}

	//3
	lis3.InsertColumn(0, "商品编码", LVCFMT_LEFT, 80);
	lis3.InsertColumn(1, "名称", LVCFMT_LEFT, 160);
	lis3.InsertColumn(2, "库存数量", LVCFMT_LEFT, 80);
	lis3.InsertColumn(3, "商品进价", LVCFMT_LEFT, 80);
	lis3.InsertColumn(4, "商品销售价", LVCFMT_LEFT, 100);
	lis3.Update(0);

	CString se3;
	se3.Format("SELECT * FROM 商品;");
	mysql_query(&mq, se3);
	MYSQL_RES* res3 = mysql_store_result(&mq);
	for (int i = 0; i < res3->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res3);
		int itemIndex = lis3.InsertItem(0, _T("")); // 插入新行
		lis3.SetItemText(itemIndex, 0, row[0]);
		lis3.SetItemText(itemIndex, 1, row[1]);
		lis3.SetItemText(itemIndex, 2, row[2]);
		lis3.SetItemText(itemIndex, 3, row[3]);
		lis3.SetItemText(itemIndex, 4, row[4]);
		lis3.Update(itemIndex);
	}

	//4
	lis4.InsertColumn(0, "身份证号码", LVCFMT_LEFT, 150);
	lis4.InsertColumn(1, "商品编码", LVCFMT_LEFT, 80);
	lis4.InsertColumn(2, "销售时间", LVCFMT_LEFT, 200);
	lis4.InsertColumn(3, "销售商品", LVCFMT_LEFT, 150);
	lis4.InsertColumn(4, "数量", LVCFMT_LEFT, 80);
	lis4.Update(0);

	CString se4;
	se4.Format("SELECT * FROM 销售;");
	mysql_query(&mq, se4);
	MYSQL_RES* res4 = mysql_store_result(&mq);
	for (int i = 0; i < res4->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res4);
		int itemIndex = lis4.InsertItem(0, _T("")); // 插入新行
		lis4.SetItemText(itemIndex, 0, row[0]);
		lis4.SetItemText(itemIndex, 1, row[1]);
		lis4.SetItemText(itemIndex, 2, row[2]);
		lis4.SetItemText(itemIndex, 3, row[3]);
		lis4.SetItemText(itemIndex, 4, row[4]);
		lis4.Update(itemIndex);
	}

	//5
	lis5.InsertColumn(0, "商品编码", LVCFMT_LEFT, 80);
	lis5.InsertColumn(1, "身份证号码", LVCFMT_LEFT, 150);
	lis5.InsertColumn(2, "入库数量", LVCFMT_LEFT, 80);
	lis5.InsertColumn(3, "入库时间", LVCFMT_LEFT, 178);
	lis5.Update(0);

	CString se5;
	se5.Format("SELECT * FROM 采购、入库;");
	mysql_query(&mq, se5);
	MYSQL_RES* res5 = mysql_store_result(&mq);
	for (int i = 0; i < res5->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res5);
		int itemIndex = lis5.InsertItem(0, _T("")); // 插入新行
		lis5.SetItemText(itemIndex, 0, row[0]);
		lis5.SetItemText(itemIndex, 1, row[1]);
		lis5.SetItemText(itemIndex, 2, row[2]);
		lis5.SetItemText(itemIndex, 3, row[3]);
		lis5.Update(itemIndex);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void myadmin::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = -1;
	sel = lis1.GetNextItem(sel, LVNI_SELECTED);
	lis1.SetItemState(sel, 0, LVIS_SELECTED);
	if (sel == -1)
	{
		CString s1, s2;
		bmbh.GetWindowTextA(s1);
		bmmc.GetWindowTextA(s2);
		if (s1 == "" || s2 == "")
		{
			MessageBox("输入项不能为空！");
			return;
		}
		//
		int co = lis1.GetItemCount();
		for (int i = 0; i < co; i++)
		{
			CString ss = lis1.GetItemText(i, 0);
			if (ss == s1)
			{
				goto L;
			}
		}
		//
		CString ins;
		ins.Format("insert into 部门 values ('%s','%s');", s1,s2);
		if (!mysql_query(&mq, ins))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}
		//
		CString se;
		se.Format("SELECT * FROM 部门 WHERE 部门编号='%s';", s1);
		mysql_query(&mq, se);
		MYSQL_RES* res = mysql_store_result(&mq);
		MYSQL_ROW row = mysql_fetch_row(res);

		// 设置每列的文本
		int itemIndex = lis1.InsertItem(0, _T("")); // 插入新行
		lis1.SetItemText(itemIndex, 0, row[0]);
		lis1.SetItemText(itemIndex, 1, row[1]);
		lis1.Update(itemIndex);
	}
	else
	{
	L:
		CString str;
		str = lis1.GetItemText(sel, 0);
		CString s1, s2;
		bmbh.GetWindowTextA(s1);
		bmmc.GetWindowTextA(s2);
		if (s1 == "" || s2 == "")
		{
			MessageBox("输入项不能为空！");
			return;
		}
		CString upd;
		upd.Format("update 部门 set 部门名称='%s' where 部门编号='%s';", s2, s1);
		if (!mysql_query(&mq, upd))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}
		//
		int co=lis1.GetItemCount();
		int poi = -1;
		for (int i = 0; i < co; i++)
		{
			CString ss = lis1.GetItemText(i, 0);
			if (ss == s1)
			{
				poi = i;
				break;
			}
		}
		lis1.SetItemText(poi, 1, s2);
		lis1.Update(poi);
	}
}


void myadmin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = -1;
	sel = lis1.GetNextItem(sel, LVNI_SELECTED);
	lis1.SetItemState(sel, 0, LVIS_SELECTED);
	if (sel == -1)
	{
		MessageBox("错误，未选中需要删除的项");
	}
	else
	{
		CString str;
		str = lis1.GetItemText(sel, 0);
		CString del;
		del.Format("delete from 部门 where 部门编号='%s';", str);
		if (!mysql_query(&mq, del))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}
		lis1.DeleteItem(sel);
		//
		lis1.ShowWindow(SW_HIDE);
		int nTopIndex = lis1.GetTopIndex();
		int nCountPerPage = lis1.GetCountPerPage();
		lis1.RedrawItems(nTopIndex, nTopIndex + nCountPerPage);
		lis1.ShowWindow(SW_SHOW);
	}
}


void myadmin::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = -1;
	sel = lis2.GetNextItem(sel, LVNI_SELECTED);
	lis2.SetItemState(sel, 0, LVIS_SELECTED);
	if (sel == -1)
	{
		CString s1, s2, s3, s4, s5, s6;
		ygsfz.GetWindowTextA(s1);
		ygxm.GetWindowTextA(s2);
		ygxb.GetWindowTextA(s3);
		ygbmbh.GetWindowTextA(s4);
		ygzh.GetWindowTextA(s5);
		ygmm.GetWindowTextA(s6);
		if (s1 == "" || s2 == "" || s3 == "" || s4 == "" || s5 == "" || s6 == "")
		{
			MessageBox("输入项不能为空！");
			return;
		}

		//
		int co = lis2.GetItemCount();
		for (int i = 0; i < co; i++)
		{
			CString ss = lis2.GetItemText(i, 0);
			if (ss == s1)
			{
				goto L;
			}
		}
		//
		CString ins;
		ins.Format("insert into 员工 values ('%s','%s','%s','%s','%s','%s');", s1, s4, s2, s3, s5, s6);
		if (!mysql_query(&mq, ins))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}

		if (s4 == "1")
		{
			ins.Format("insert into 收银员 values ('%s','%s','%s','%s','%s','%s');", s1, s4, s2, s3, s5, s6);
			mysql_query(&mq, ins);
		}
		else if (s4 == "2")
		{
			ins.Format("insert into 采购员 values ('%s','%s','%s','%s','%s','%s');", s1, s4, s2, s3, s5, s6);
			mysql_query(&mq, ins);
		}

		//
		CString se;
		se.Format("SELECT * FROM 员工 WHERE 身份证号码='%s';", s1);
		mysql_query(&mq, se);
		MYSQL_RES* res = mysql_store_result(&mq);
		MYSQL_ROW row = mysql_fetch_row(res);

		// 设置每列的文本
		int itemIndex = lis2.InsertItem(0, _T("")); // 插入新行
		lis2.SetItemText(itemIndex, 0, row[0]);
		lis2.SetItemText(itemIndex, 1, row[1]);
		lis2.SetItemText(itemIndex, 2, row[2]);
		lis2.SetItemText(itemIndex, 3, row[3]);
		lis2.SetItemText(itemIndex, 4, row[4]);
		lis2.SetItemText(itemIndex, 5, row[5]);
		lis2.Update(itemIndex);
	}
	else
	{
	L:
		CString str;
		str = lis2.GetItemText(sel, 0);
		CString s1, s2, s3, s4, s5, s6;
		ygsfz.GetWindowTextA(s1);
		ygxm.GetWindowTextA(s2);
		ygxb.GetWindowTextA(s3);
		ygbmbh.GetWindowTextA(s4);
		ygzh.GetWindowTextA(s5);
		ygmm.GetWindowTextA(s6);
		if (s1 == "" || s2 == "" || s3 == "" || s4 == "" || s5 == "" || s6 == "")
		{
			MessageBox("输入项不能为空！");
			return;
		}
		CString upd;
		upd.Format("update 员工 set 部门编号='%s',姓名='%s',性别='%s',账号='%s',密码='%s' where 身份证号码='%s';", s4, s2, s3, s5, s6, s1);
		if (!mysql_query(&mq, upd))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}
		//
		int co = lis2.GetItemCount();
		int poi = -1;
		for (int i = 0; i < co; i++)
		{
			CString ss = lis2.GetItemText(i, 0);
			if (ss == s1)
			{
				poi = i;
				break;
			}
		}
		lis2.SetItemText(poi, 1, s4);
		lis2.SetItemText(poi, 2, s2);
		lis2.SetItemText(poi, 3, s3);
		lis2.SetItemText(poi, 4, s5);
		lis2.SetItemText(poi, 5, s6);
		lis2.Update(poi);
	}
}


void myadmin::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = -1;
	sel = lis2.GetNextItem(sel, LVNI_SELECTED);
	lis2.SetItemState(sel, 0, LVIS_SELECTED);
	if (sel == -1)
	{
		MessageBox("错误，未选中需要删除的项");
	}
	else
	{
		CString str;//str是身份证号码
		CString bmm;//bmm是部门编号
		str = lis2.GetItemText(sel, 0);
		bmm = lis2.GetItemText(sel, 1);
		CString del;
		del.Format("START TRANSACTION;");
		mysql_query(&mq, del);
		if (bmm = "1")
		{
			del.Format("delete from 收银员 where 身份证号码='%s';",str);
			mysql_query(&mq, del);
			del.Format("delete from 员工 where 身份证号码='%s';", str);
			mysql_query(&mq, del);
			del.Format("COMMIT;");
			if (!mysql_query(&mq, del))
			{
				MessageBox("操作成功！");
			}
			else
			{
				MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
				return;
			}
		}
		else if(bmm="2")
		{
			del.Format("delete from 采购员 where 身份证号码='%s';", str);
			mysql_query(&mq, del);
			del.Format("delete from 员工 where 身份证号码='%s';", str);
			mysql_query(&mq, del);
			del.Format("COMMIT;");
			if (!mysql_query(&mq, del))
			{
				MessageBox("操作成功！");
			}
			else
			{
				MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
				return;
			}
		}
		lis2.DeleteItem(sel);
		//
		lis2.ShowWindow(SW_HIDE);
		int nTopIndex = lis2.GetTopIndex();
		int nCountPerPage = lis2.GetCountPerPage();
		lis2.RedrawItems(nTopIndex, nTopIndex + nCountPerPage);
		lis2.ShowWindow(SW_SHOW);
	}

}


void myadmin::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = -1;
	sel = lis3.GetNextItem(sel, LVNI_SELECTED);
	lis3.SetItemState(sel, 0, LVIS_SELECTED);
	if (sel == -1)
	{
		CString s1, s2, s3, s4, s5;
		spbm.GetWindowTextA(s1);
		spmc.GetWindowTextA(s2);
		spkc.GetWindowTextA(s3);
		spjj.GetWindowTextA(s4);
		spxsj.GetWindowTextA(s5);
		if (s1 == "" || s2 == "" || s3 == "" || s4 == "" || s5 == "" )
		{
			MessageBox("输入项不能为空！");
			return;
		}
		//
		int co = lis3.GetItemCount();
		for (int i = 0; i < co; i++)
		{
			CString ss = lis3.GetItemText(i, 0);
			if (ss == s1)
			{
				goto L;
			}
		}
		//
		CString ins;
		ins.Format("insert into 商品 values ('%s','%s','%s','%s','%s');", s1, s2, s3, s4, s5);
		if (!mysql_query(&mq, ins))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}
		//
		CString se;
		se.Format("SELECT * FROM 商品 WHERE 商品编码='%s';", s1);
		mysql_query(&mq, se);
		MYSQL_RES* res = mysql_store_result(&mq);
		MYSQL_ROW row = mysql_fetch_row(res);

		// 设置每列的文本
		int itemIndex = lis3.InsertItem(0, _T("")); // 插入新行
		lis3.SetItemText(itemIndex, 0, row[0]);
		lis3.SetItemText(itemIndex, 1, row[1]);
		lis3.SetItemText(itemIndex, 2, row[2]);
		lis3.SetItemText(itemIndex, 3, row[3]);
		lis3.SetItemText(itemIndex, 4, row[4]);
		lis3.Update(itemIndex);
	}
	else
	{
	L:
		CString str;
		str = lis3.GetItemText(sel, 0);
		CString s1, s2, s3, s4, s5;
		spbm.GetWindowTextA(s1);
		spmc.GetWindowTextA(s2);
		spkc.GetWindowTextA(s3);
		spjj.GetWindowTextA(s4);
		spxsj.GetWindowTextA(s5);
		if (s1 == "" || s2 == "" || s3 == "" || s4 == "" || s5 == "" )
		{
			MessageBox("输入项不能为空！");
			return;
		}
		CString upd;
		upd.Format("update 商品 set 名称='%s',库存数量='%s',商品进价='%s',商品销售价='%s' where 商品编码='%s';", s2, s3, s4, s5, s1);
		if (!mysql_query(&mq, upd))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}
		//
		int co = lis3.GetItemCount();
		int poi = -1;
		for (int i = 0; i < co; i++)
		{
			CString ss = lis3.GetItemText(i, 0);
			if (ss == s1)
			{
				poi = i;
				break;
			}
		}
		lis3.SetItemText(poi, 1, s2);
		lis3.SetItemText(poi, 2, s3);
		lis3.SetItemText(poi, 3, s4);
		lis3.SetItemText(poi, 4, s5);
		lis3.Update(poi);
	}
}


void myadmin::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = -1;
	sel = lis3.GetNextItem(sel, LVNI_SELECTED);
	lis3.SetItemState(sel, 0, LVIS_SELECTED);
	if (sel == -1)
	{
		MessageBox("错误，未选中需要删除的项");
	}
	else
	{
		CString str;
		str = lis3.GetItemText(sel, 0);
		CString del;
		del.Format("delete from 商品 where 商品编码='%s';", str);
		if (!mysql_query(&mq, del))
		{
			MessageBox("操作成功！");
		}
		else
		{
			MessageBox("执行操作失败，请检查数据合法性或联系管理员！");
			return;
		}		lis3.DeleteItem(sel);
		//
		lis3.ShowWindow(SW_HIDE);
		int nTopIndex = lis3.GetTopIndex();
		int nCountPerPage = lis3.GetCountPerPage();
		lis3.RedrawItems(nTopIndex, nTopIndex + nCountPerPage);
		lis3.ShowWindow(SW_SHOW);
	}

}


void myadmin::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	lis4.DeleteAllItems();
	lis5.DeleteAllItems();
	CString se4;
	se4.Format("SELECT * FROM 销售;");
	mysql_query(&mq, se4);
	MYSQL_RES* res4 = mysql_store_result(&mq);
	for (int i = 0; i < res4->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res4);
		int itemIndex = lis4.InsertItem(0, _T("")); // 插入新行
		lis4.SetItemText(itemIndex, 0, row[0]);
		lis4.SetItemText(itemIndex, 1, row[1]);
		lis4.SetItemText(itemIndex, 2, row[2]);
		lis4.SetItemText(itemIndex, 3, row[3]);
		lis4.SetItemText(itemIndex, 4, row[4]);
		lis4.Update(itemIndex);
	}
	CString se5;
	se5.Format("SELECT * FROM 采购、入库;");
	mysql_query(&mq, se5);
	MYSQL_RES* res5 = mysql_store_result(&mq);
	for (int i = 0; i < res5->row_count; i++)
	{
		MYSQL_ROW row = mysql_fetch_row(res5);
		int itemIndex = lis5.InsertItem(0, _T("")); // 插入新行
		lis5.SetItemText(itemIndex, 0, row[0]);
		lis5.SetItemText(itemIndex, 1, row[1]);
		lis5.SetItemText(itemIndex, 2, row[2]);
		lis5.SetItemText(itemIndex, 3, row[3]);
		lis5.Update(itemIndex);
	}
	MessageBox("更新成功！");
}


void myadmin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
