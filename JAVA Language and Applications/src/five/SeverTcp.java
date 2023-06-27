package five;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;

import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.player.Player;

//操作：
//1代表下棋
//2代表文字聊天
//3代表表情包
//4代表语音包
//5代表悔棋
//6代表认输
//7代表重新开始
//8代表失败
//服务器端为黑棋
public class SeverTcp {
	static int dk;
	static Socket s;
	static boolean sestart = false;// 开始默认黑子先下

	SeverTcp(ChessJFrame cjf) throws Exception {
		sestart = true;
		ChessBord.GameStart = true;
		try (ServerSocket ss = new ServerSocket(dk)) {
			Chat.a1.append("端口" + dk + "服务器开启" + "\n");
			Chat.a1.paintImmediately(Chat.a1.getBounds());
			s = ss.accept();
		}
		Chat.a1.append("端口" + dk + "服务器开启成功！" + "\n");
		Chat.a1.paintImmediately(Chat.a1.getBounds());
		BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
		PrintWriter out = new PrintWriter(s.getOutputStream(), true);

		// 添加接收线程
		new Thread() {
			public void run() {
				String line = null;
				try {
					while ((line = in.readLine()) != null) {
						int pl = line.charAt(0) - 48;
						line = line.substring(2);
						if (pl == 1) {
							// 下棋
							// 文本格式为1,x,y
							// line为*+x+y;
							int xx;
							int yy;
							xx = getxx(line);
							yy = getyy(line);
							ChessJFrame.chessbord.pickchess(xx, yy);
							// Chat.a1.append("对方下棋" + "\n");
							// Chat.a1.paintImmediately(Chat.a1.getBounds());
						} else if (pl == 2) {
							// 文字
							String ll = "对方向您发送了:";
							ll = ll + line;
							Chat.a2.append(ll + "\n");
							Chat.a2.paintImmediately(Chat.a1.getBounds());
						} else if (pl == 3) {
							// 表情包
							Chat.a2.append("对方向您发送了表情" + "\n");
							Chat.a2.paintImmediately(Chat.a1.getBounds());
							Chat.ct.changep(Integer.parseInt(line));
							Chat.ca.remove(Chat.jsc1);
							Chat.ca.repaint();
							Chat.ca.add(Chat.ct, BorderLayout.NORTH);
							Timer timer = new Timer("test-timer");
							// 定义一个TimerTask
							// 延时恢复文本框，取消表情展示
							TimerTask task = new TimerTask() {
								@Override
								public void run() {
									Chat.ca.remove(Chat.ct);
									Chat.ca.repaint();
									Chat.ca.add(Chat.jsc1, BorderLayout.NORTH);
								}
							};
							long delay = 3000L;
							timer.schedule(task, delay);
						} else if (pl == 4) {
							// 语音
							Chat.a2.append("对方向您发送了语音: " + line + "\n");
							Chat.a2.paintImmediately(Chat.a1.getBounds());
							String fname = line;
							fname = "res/yuyin/" + fname + ".mp3";
							File file = new File(fname);
							FileInputStream fis = null;
							try {
								fis = new FileInputStream(file);
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
						} else if (pl == 5) {
							ChessJFrame.chessbord.goback();
						} else if (pl == 6) {
							ChessJFrame.chessbord.end();
						} else if (pl == 7) {
							ChessJFrame.chessbord.restartGame();
						}
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			};
		}.start();

		// 绑定监听器
		Chat.b1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 发送按钮
				// 聊天
				String inp = Chat.a3.getText();
				if (!inp.equals("空")) {
					String fp = "您向对方发送:[" + inp + "]";
					String ffp = "成功";
					inp = "2," + inp;
					Chat.a1.append(fp + "\n");
					Chat.a1.append(ffp + "\n");
					Chat.a1.paintImmediately(Chat.a1.getBounds());
					out.println(inp);
					Chat.a3.setText("空");
				}
				// 表情
				String bqt = Chat.bq;
				if (bqt.equals("0")) {
					;
				} else {
					//
					Chat.a1.append("您向对方发送了表情" + "\n");
					Chat.a1.paintImmediately(Chat.a1.getBounds());
					out.println("3," + bqt);
					Chat.bq = "0";
				}
				// 语音
				String yyt = Chat.yy;
				if (yyt.equals("无")) {
					;
				} else {
					//
					Chat.a1.append("您向对方发送了语音:" + yyt + "\n");
					Chat.a1.paintImmediately(Chat.a1.getBounds());
					out.println("4," + yyt);
					Chat.yy = "无";
				}
			}
		});
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
		while (a.charAt(str) != ',') {
			p = p + a.charAt(str);
			str = str + 1;
			if (str == a.length()) {
				break;
			}
		}
		return Integer.parseInt(p);
	}

}
