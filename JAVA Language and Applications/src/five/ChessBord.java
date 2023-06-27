package five;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;

import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.player.Player;

public class ChessBord extends JPanel implements MouseListener {// 继承面板类和鼠标事件接口
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static int MARGIN = 20;// 定义边距
	public static int ROWS = 15;// 定义行数
	public static int COLS = 15;// 定义列数
	public static int GRID_SPAN = 35;// 网格间距
	Chess[] chessList = new Chess[(ROWS + 1) * (COLS + 1)];// 定义一个棋子数组
	String[][] board = new String[MARGIN * 2 + GRID_SPAN * COLS][MARGIN * 2 + GRID_SPAN * COLS];// 声明一个字符串数组，用来判断输赢
	int chessCount;// 棋子数目
	int xindex, yindex;// 棋子的坐标索引
	boolean start = true;// 开始默认黑子先下
	static boolean GameOver = false;// 定义是否游戏结束
	static boolean GameStart = false;
	boolean replay = false;

	public ChessBord() {// 棋盘类构造函数
		this.setSize(600, 600);
		addMouseListener(this);// 将棋盘类添加到鼠标事件监听器
		addMouseMotionListener(new MouseMotionListener() {// 匿名内部类
			@Override
			public void mouseMoved(MouseEvent e) {// 根据鼠标的移动所在的坐标来设置鼠标光标形状
				int x1 = (e.getX() - MARGIN + GRID_SPAN / 2) / GRID_SPAN;// 对鼠标光标的x坐标进行转换
				int y1 = (e.getY() - MARGIN + GRID_SPAN / 2) / GRID_SPAN;// 对鼠标光标的y坐标进行转换
				if (x1 < 0 || x1 > ROWS || y1 < 0 || y1 > COLS || GameOver || findchess(x1, y1)) {
					setCursor(new Cursor(Cursor.DEFAULT_CURSOR));// 设置鼠标光标为默认形状
				} else {
					setCursor(new Cursor(Cursor.HAND_CURSOR));// 设置鼠标光标为手型
				}
			}

			@Override
			public void mouseDragged(MouseEvent e) {
			}
		});
		for (int i = 0; i < MARGIN * 2 + GRID_SPAN * COLS; i++) {// 对board[][]赋初值
			for (int j = 0; j < MARGIN * 2 + GRID_SPAN * COLS; j++) {
				board[i][j] = "0";
			}
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
	}

	@Override
	public void mousePressed(MouseEvent e) {// 鼠标点击事件
		if (GameOver)// 游戏结束，不能按
			return;
		if (!GameStart)// 未开始
			return;
		if (replay)// 复盘中
			return;
		if (seeTcp.issee == 1) {
			return;// 观战中
		}
		if (SeverTcp.sestart == true && ClientTcp.clstart == true && start == false) {
			// 我为服务器端
			return;
		}
		if (SeverTcp.sestart == false && ClientTcp.clstart == false && start == true) {
			// 我为客户端
			return;
		}
		String colorName = start ? "黑棋" : "白棋";// 判断是什么颜色的棋子
		xindex = (e.getX() - MARGIN + GRID_SPAN / 2) / GRID_SPAN;// 得到棋子x坐标
		yindex = (e.getY() - MARGIN + GRID_SPAN / 2) / GRID_SPAN;// 得到棋子y坐标
		board[xindex][yindex] = colorName;// 以棋子x坐标y坐标做索引将棋子的颜色添加到board中
		if (xindex < 0 || xindex > ROWS || yindex < 0 || yindex > COLS) {// 棋子在棋盘外不能下，
			return;
		} else if (findchess(xindex, yindex)) {// 所下位置已有棋子，不能下
			return;
		}
		Chess po = new Chess(xindex, yindex, start ? Color.black : Color.WHITE);// 对棋子对象进行初始化
		chessList[chessCount++] = po;// 将棋子对象添加到棋子数组中
		repaint();// 重画图型
		if (win(xindex, yindex, start)) {// 判断是否胜利
			dowin();
			// gameOver=true;
			GameOver = true;
		} else if (chessCount == (COLS + 1) * (ROWS + 1)) {// 判断是否全部下满
			String msg = String.format("恭喜 %s赢了", colorName);
			JOptionPane.showMessageDialog(this, msg);
			GameOver = true;
		}

		// 添加下棋音效
		File pickmusi = new File("res/5390.mp3");
		FileInputStream fis = null;
		try {
			fis = new FileInputStream(pickmusi);
		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		BufferedInputStream stream = new BufferedInputStream(fis);
		Player player = null;
		try {
			player = new Player(stream);
		} catch (JavaLayerException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			player.play();
		} catch (JavaLayerException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		// 发送给对方下棋
		String stf = "1," + Integer.toString(xindex) + "," + Integer.toString(yindex);
		if (ChessJFrame.tse == 1) {
			try {
				PrintWriter out = new PrintWriter(SeverTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (ChessJFrame.tse == 2) {
			try {
				PrintWriter out = new PrintWriter(ClientTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
		// 发送观战
		String seestf = "1," + Integer.toString(xindex) + "," + Integer.toString(yindex);
		if (ChessJFrame.seeis == 1) {
			try {
				PrintWriter out = new PrintWriter(ChessJFrame.seetcp.getOutputStream(), true);
				out.println(seestf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}

		//
		start = !start;// 改变棋子先下棋状态

	}

	@Override
	public void mouseReleased(MouseEvent e) {
	}

	@Override
	public void mouseEntered(MouseEvent e) {
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	public void pickchess(int fx, int fy) {
		// 添加下棋音效
		File pickmusi = new File("res/5390.mp3");
		FileInputStream fis = null;
		try {
			fis = new FileInputStream(pickmusi);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		BufferedInputStream stream = new BufferedInputStream(fis);
		Player player = null;
		try {
			player = new Player(stream);
		} catch (JavaLayerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			player.play();
		} catch (JavaLayerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (seeTcp.issee == 1) {
			System.out.println("观战方下棋");
		}
		//
		String colorName = start ? "黑棋" : "白棋";// 判断是什么颜色的棋子
		xindex = fx;
		yindex = fy;
		board[xindex][yindex] = colorName;// 以棋子x坐标y坐标做索引将棋子的颜色添加到board中
		if (xindex < 0 || xindex > ROWS || yindex < 0 || yindex > COLS) {// 棋子在棋盘外不能下，
			return;
		} else if (findchess(xindex, yindex)) {// 所下位置已有棋子，不能下
			return;
		}
		Chess po = new Chess(xindex, yindex, start ? Color.black : Color.WHITE);// 对棋子对象进行初始化
		chessList[chessCount++] = po;// 将棋子对象添加到棋子数组中
		repaint();// 重画图型
		if (win(xindex, yindex, start)) {// 判断是否胜利
			dolose();
			GameOver = true;
		} else if (chessCount == (COLS + 1) * (ROWS + 1)) {// 判断是否全部下满

			GameOver = true;
		}

		// 发送观战
		String seestf = "1," + Integer.toString(xindex) + "," + Integer.toString(yindex);
		if (ChessJFrame.seeis == 1) {
			try {
				PrintWriter out = new PrintWriter(ChessJFrame.seetcp.getOutputStream(), true);
				out.println(seestf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}

		start = !start;// 改变棋子先下棋状态
	}

	public void dowin() {
		// 播放胜利音效
		String msg = "恭喜您赢了！";
		JOptionPane.showMessageDialog(this, msg);

		File wimusi = new File("res/15431.mp3");
		FileInputStream fis = null;
		try {
			fis = new FileInputStream(wimusi);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		BufferedInputStream stream = new BufferedInputStream(fis);
		Player player = null;
		try {
			player = new Player(stream);
		} catch (JavaLayerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			player.play();
		} catch (JavaLayerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		String stf = "8,66666";
		if (ChessJFrame.tse == 1) {
			try {
				PrintWriter out = new PrintWriter(SeverTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (ChessJFrame.tse == 2) {
			try {
				PrintWriter out = new PrintWriter(ClientTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}

	}

	public void dolose() {
		String msg = "哦，抱歉您输了！";
		JOptionPane.showMessageDialog(this, msg);

		File wimusi = new File("res/13157.mp3");
		FileInputStream fis = null;
		try {
			fis = new FileInputStream(wimusi);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		BufferedInputStream stream = new BufferedInputStream(fis);
		Player player = null;
		try {
			player = new Player(stream);
		} catch (JavaLayerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			player.play();
		} catch (JavaLayerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void end() {
		dowin();
		GameOver = true;
	}

	public void renshu() {

		String stf = "6,66666";
		if (ChessJFrame.tse == 1) {
			try {
				PrintWriter out = new PrintWriter(SeverTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (ChessJFrame.tse == 2) {
			try {
				PrintWriter out = new PrintWriter(ClientTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
		GameOver = true;
		dolose();
	}

	@Override
	protected void paintComponent(Graphics g) {
		// 画棋盘
		super.paintComponents(g);
		ImageIcon ic = new ImageIcon("res/qq.jpg");
		Image d = ic.getImage();
		g.drawImage(d, 0, 0, this.getWidth(), this.getHeight(), this);
		for (int i = 0; i <= ROWS; i++) {// 画横线
			g.drawLine(MARGIN, MARGIN + i * GRID_SPAN, MARGIN + COLS * GRID_SPAN, MARGIN + i * GRID_SPAN);
		}
		for (int j = 0; j <= COLS; j++) {// 画竖线
			g.drawLine(MARGIN + j * GRID_SPAN, MARGIN, MARGIN + j * GRID_SPAN, MARGIN + ROWS * GRID_SPAN);
		}
		for (int i = 0; i < chessCount; i++) {// 画棋子
			int xpos = chessList[i].getX() * GRID_SPAN + MARGIN;// 得到棋子x坐标
			int ypos = chessList[i].getY() * GRID_SPAN + MARGIN;// 得到棋子y坐标
			g.setColor(chessList[i].getColor());// 设置棋子颜色
			ImageIcon cb = new ImageIcon("res/black.png");
			ImageIcon cw = new ImageIcon("res/white.png");
			Image che;
			if (g.getColor() == Color.black) {
				che = cb.getImage();
			} else {
				che = cw.getImage();
			}
			g.drawImage(che, xpos - Chess.DIAMETER / 2, ypos - Chess.DIAMETER / 2, Chess.DIAMETER, Chess.DIAMETER,
					this);
			if (i == chessCount - 1) {
				g.setColor(Color.red);// 标记最后一个棋子为红色
				g.drawRect(xpos - Chess.DIAMETER / 2, ypos - Chess.DIAMETER / 2, Chess.DIAMETER, Chess.DIAMETER);
			}
		}
		Font fo = new Font("黑体", 1, 20);
		g.setFont(fo);
		g.setColor(Color.BLACK);
		if (GameOver == true) {
			g.drawString("游戏结束", 230, 590);
		} else {
			if (GameStart == false) {
				g.drawString("游戏未开始", 220, 590);
			} else {
				if (SeverTcp.sestart == true && ClientTcp.clstart == true) {
					// 服务器端
					if (start == true) {
						g.drawString("请您下棋", 230, 590);
					} else {
						g.drawString("等待对方下棋", 210, 590);
					}

				} else if (SeverTcp.sestart == false && ClientTcp.clstart == false) {
					// 客户端
					if (start == false) {
						g.drawString("请您下棋", 230, 590);
					} else {
						g.drawString("等待对方下棋", 220, 590);
					}

				}
			}

		}

	}

	private boolean findchess(int index, int yindex) {// 查找所在位置是否有棋子
		for (Chess c : chessList) {
			if (c != null && c.getX() == xindex && c.getY() == yindex)
				return true;
		}
		return false;
	}

	private boolean win(int x, int y, boolean start) {// 对棋子输赢的判断
		String str = start ? "黑棋" : "白棋";
		// 棋子所在行和列是否有五子相连的情况
		for (int i = 0; i < 16; i++) {
			if ((board[x][i].equals(str) && board[x][i + 1].equals(str) && board[x][i + 2].equals(str)
					&& board[x][i + 3].equals(str) && board[x][i + 4].equals(str))
					|| (board[i][y].equals(str) && board[i + 1][y].equals(str) && board[i + 2][y].equals(str)
							&& board[i + 3][y].equals(str) && board[i + 4][y].equals(str)))
				return true;
		}
		// 棋子所在撇行是否有五子相连的情况
		if (x + y >= 4 && x + y <= 30) {
			int i = (x + y <= 19) ? x + y : x + y - 20;
			if (x + y <= 19) {
				for (int k = 0; k <= i - 4; k++) {
					if (board[k][i - k].equals(str) && board[k + 1][i - k - 1].equals(str)
							&& board[k + 2][i - k - 2].equals(str) && board[k + 3][i - k - 3].equals(str)
							&& board[k + 4][i - k - 4].equals(str))
						return true;
				}
			} else {
				for (int k = i; k <= 15; k++) {
					if (board[k][20 - k].equals(str) && board[k + 1][20 - k - 1].equals(str)
							&& board[k + 2][20 - k - 2].equals(str) && board[k + 3][20 - k - 3].equals(str)
							&& board[k + 4][20 - k - 4].equals(str))
						return true;
				}
			}
		}
		// 棋子所在捺行是否有五子相连的情况
		if (y - x <= 15 && x - y <= 15) {
			int i = (x < y) ? y - x : x - y;
			if (x < y) {
				for (int k = 0; k <= 19 - 4 - i; k++) {
					if (board[k][i + k].equals(str) && board[k + 1][i + k + 1].equals(str)
							&& board[k + 2][i + k + 2].equals(str) && board[k + 3][i + k + 3].equals(str)
							&& board[k + 4][i + k + 4].equals(str))
						return true;
				}
			} else {
				for (int k = i; k <= 15; k++) {
					if (board[k][i + k].equals(str) && board[k + 1][i + k + 1].equals(str)
							&& board[k + 2][i + k + 2].equals(str) && board[k + 3][i + k + 3].equals(str)
							&& board[k + 4][i + k + 4].equals(str))
						return true;
				}
			}
		}
		return false;
	}

	public void huiqi() {
		goback();
		String stf = "5,66666";
		if (ChessJFrame.tse == 1) {
			try {
				PrintWriter out = new PrintWriter(SeverTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (ChessJFrame.tse == 2) {
			try {
				PrintWriter out = new PrintWriter(ClientTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}

	public void goback() {// 悔棋函数
		if (chessCount == 0) {
			return;
		}
		chessList[chessCount - 1] = null;
		chessCount--;
		if (chessCount > 0) {
			xindex = chessList[chessCount - 1].getX();
			yindex = chessList[chessCount - 1].getY();
		}
		start = !start;
		repaint();
	}

	public void restart() {
		restartGame();
		String stf = "7,66666";
		if (ChessJFrame.tse == 1) {
			try {
				PrintWriter out = new PrintWriter(SeverTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (ChessJFrame.tse == 2) {
			try {
				PrintWriter out = new PrintWriter(ClientTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}

	public void restartGame() {
		// 重新开始函数
		for (int i = 0; i < chessList.length; i++)// 设置为初始状态
			chessList[i] = null;
		for (int i = 0; i < MARGIN * 2 + GRID_SPAN * COLS; i++) {
			for (int j = 0; j < MARGIN * 2 + GRID_SPAN * COLS; j++) {
				board[i][j] = "0";
			}
		}
		start = true;
		GameOver = false;
		chessCount = 0;
		repaint();
	}

	public void loadchess(String a) {
		int xx = getxx(a);
		int yy = getyy(a);
		pickchess(xx, yy);
		String stf = "1," + Integer.toString(xx) + "," + Integer.toString(yy);
		if (ChessJFrame.tse == 1) {
			try {
				PrintWriter out = new PrintWriter(SeverTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (ChessJFrame.tse == 2) {
			try {
				PrintWriter out = new PrintWriter(ClientTcp.s.getOutputStream(), true);
				out.println(stf);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}

	}

	public Dimension getPreferredSize() {// 画矩形
		return new Dimension(MARGIN * 2 + GRID_SPAN * COLS, MARGIN * 2 + GRID_SPAN * ROWS);
	}

	public void nextchess(String a) {
		int xx = getxx(a);
		int yy = getyy(a);
		pickchess(xx, yy);
	}

	int getxx(String a) {
		int str = 0;
		String p = "";
		while (a.charAt(str) != ',') {
			p = p + a.charAt(str);
			str = str + 1;
		}
		return Integer.parseInt(p);
	}

	int getyy(String a) {
		int str = 0;
		while (a.charAt(str) != ',') {
			str = str + 1;
		}
		str = str + 1;
		String p = "";
		while (a.charAt(str) != ',' && a.charAt(str) != '\n') {
			p = p + a.charAt(str);
			str = str + 1;
			if (str == a.length()) {
				break;
			}
		}
		return Integer.parseInt(p);
	}

}
