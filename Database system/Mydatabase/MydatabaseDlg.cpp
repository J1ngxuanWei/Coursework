
// MydatabaseDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Mydatabase.h"
#include "MydatabaseDlg.h"
#include "afxdialogex.h"

#include "winsock.h"
#include "mysql.h"

#include "myadminview.h"
#include "mycg.h"
#include "mysy.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMydatabaseDlg 对话框



CMydatabaseDlg::CMydatabaseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYDATABASE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMydatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, mtext);
	DDX_Control(pDX, IDC_STATIC2, mtext2);
	DDX_Control(pDX, IDC_STATIC3, mtext3);
	DDX_Control(pDX, IDC_STATIC4, mtext4);
	DDX_Control(pDX, IDC_EDIT2, t1);
	DDX_Control(pDX, IDC_EDIT3, t2);
}

BEGIN_MESSAGE_MAP(CMydatabaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMydatabaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMydatabaseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMydatabaseDlg 消息处理程序

BOOL CMydatabaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mysql_init(&mq);
	mysql_real_connect(&mq, "localhost", "root", "wjx20021002", "supermarket", 3306, NULL, 0);
	mysql_query(&mq, "set names 'gb2312'");


	myf.CreatePointFont(250, _T("Times New Roman"));  //Times New Roman
	mtext.SetFont(&myf);
	myf2.CreatePointFont(150, _T("Times New Roman"));  //Times New Roman
	mtext2.SetFont(&myf2);
	myf3.CreatePointFont(100, _T("Times New Roman"));  //Times New Roman
	mtext3.SetFont(&myf3);
	myf4.CreatePointFont(100, _T("Times New Roman"));  //Times New Roman
	mtext4.SetFont(&myf4);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMydatabaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMydatabaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMydatabaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMydatabaseDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString n;
	CString nn = "admin";
	CString pass;
	CString ps = "112233";
	t1.GetWindowText(n);
	t2.GetWindowText(pass);
	if (n.Compare(nn) == 0)
	{
		if (pass.Compare(ps) == 0)
		{
			ShowWindow(SW_HIDE);
			myadminview* pDlg = new myadminview;
			pDlg->Create(IDD_DIALOG4, this);    //创建对话框
			pDlg->CenterWindow();
			pDlg->ShowWindow(SW_SHOW);    //显示对话框
		}
		else
		{
			MessageBox("密码错误，请重新输入");
		}
	}
	else
	{
		CString se;
		CString p;
		se.Format("SELECT 密码 FROM 员工 WHERE 账号='%s';",n);
		int ress = mysql_query(&mq,se);
		if (ress == 0) //检测查询成功
		{
			MYSQL_RES*res = mysql_store_result(&mq);
			if (mysql_num_rows(res) == 0) //查询结果为空
			{
				MessageBox(_T("账号不存在"));
			}
			else
			{
				MYSQL_ROW row = mysql_fetch_row(res);
				p = row[0];
				if (p.Compare(pass) == 0)
				{
					if (n.GetAt(0) == 's')
					{
						ShowWindow(SW_HIDE);
						mysy* pDlg = new mysy;
						pDlg->Create(IDD_DIALOG1, this);    //创建对话框
						pDlg->CenterWindow();
						pDlg->setinf(n);
						pDlg->ShowWindow(SW_SHOW);    //显示对话框
					}
					else if (n.GetAt(0) == 'c')
					{
						ShowWindow(SW_HIDE);
						mycg* pDlg = new mycg;
						pDlg->Create(IDD_DIALOG2, this);    //创建对话框
						pDlg->CenterWindow();
						pDlg->setinf(n);
						pDlg->ShowWindow(SW_SHOW);    //显示对话框
					}
				}
				else
				{
					MessageBox(_T("密码错误，请重新输入"));
				}
			}
		}
		else
		{
			AfxMessageBox(_T("访问失败!"));
		}
		
	}
}


void CMydatabaseDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
