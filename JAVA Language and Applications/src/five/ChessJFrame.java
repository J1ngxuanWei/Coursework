package five;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;

import javazoom.jl.decoder.JavaLayerException;

public class ChessJFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	static ChessBord chessbord;// 声明一个棋盘对象
	private JPanel tool; // 声明一个面板对象
	private Chat chat;
	private JButton endButton;// 声明开始按钮
	private JButton BackButton;// 声明悔棋按钮
	private JButton restart;
	private JButton save;
	private JButton load;
	private JButton rep;
	private JButton seeg;
	static JTextField jtf1;
	static JTextField jtf2;
	static SeverTcp stcp;
	static ClientTcp ctcp;
	static seeTcp setcp;
	static ServerSocket seesp;
	static Socket seetcp;
	static int tse;
	static int winlo = 0;
	static int a = 0;
	static int oop = 0;
	static int seeis = 0;
	// tse1为服务器
	// tse2为客户端

	public ChessJFrame() {// 构造函数
		setTitle("五子棋");// 设置标题
		tse = 0;
		this.setLayout(new BorderLayout());
		this.setResizable(false);
		MyButtonLister mb = new MyButtonLister();// 按钮事件处理对象
		tool = new JPanel();// 面板对象
		chessbord = new ChessBord();// 棋盘对象
		chat = new Chat(this);
		chat.setOpaque(false);
		endButton = new JButton("认输");// 设置开始按钮
		BackButton = new JButton("悔棋");// 设置悔棋按钮
		restart = new JButton("重新开始");
		save = new JButton("保存对局");
		load = new JButton("加载对局");
		rep = new JButton("复盘");
		seeg = new JButton("开启观战");
		tool.setLayout(new FlowLayout(FlowLayout.CENTER));// 流式布局
		tool.add(endButton);
		tool.add(BackButton);
		tool.add(restart);
		tool.add(save);
		tool.add(load);
		tool.add(rep);
		tool.add(seeg);
		endButton.addActionListener(mb);
		BackButton.addActionListener(mb);
		restart.addActionListener(mb);
		save.addActionListener(mb);
		load.addActionListener(mb);
		rep.addActionListener(mb);
		seeg.addActionListener(mb);
		add(chat, BorderLayout.EAST);
		add(tool, BorderLayout.SOUTH);// 按钮所在的位置
		add(chessbord, BorderLayout.CENTER);// 添加棋盘对象
		this.setSize(1100, 600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 设置关闭
		pack();// 自适应
		// 初始化
		String filePath = "res/save/all.txt";
		FileInputStream fin = null;
		try {
			fin = new FileInputStream(filePath);
		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		InputStreamReader reader = new InputStreamReader(fin);
		BufferedReader buffReader = new BufferedReader(reader);
		String strTmp = "";
		try {
			strTmp = buffReader.readLine();
			a = Integer.parseInt(strTmp);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	private class MyButtonLister implements ActionListener {
		// 按钮处理事件类
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			Object obj = e.getSource();// 获取事件源
			if (obj == endButton) {// 事件源是开始按钮
				chessbord.renshu();
			} else if (obj == BackButton) {// 事件源是悔棋按钮
				chessbord.huiqi();
			} else if (obj == restart) {
				chessbord.restart();
			} else if (obj == save) {
				String filePath = "res/save/all.txt";
				FileInputStream fin = null;
				try {
					fin = new FileInputStream(filePath);
				} catch (FileNotFoundException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				InputStreamReader reader = new InputStreamReader(fin);
				BufferedReader buffReader = new BufferedReader(reader);
				String strTmp = "";
				try {
					strTmp = buffReader.readLine();
					a = Integer.parseInt(strTmp);
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				try {
					buffReader.close();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				a = a + 1;
				writenub(filePath, Integer.toString(a));
				filePath = "res/save/" + Integer.toString(a) + ".txt";
				writeTxt(filePath, chessbord.chessList);
				String msg = "保存成功";
				JOptionPane.showMessageDialog(chessbord, msg);

			} else if (obj == load) {
				// 选择加载的局
				JFrame lo = new JFrame();
				lo.setLayout(new BorderLayout());
				JTextArea loa = new JTextArea(5, 6);
				JScrollPane lojsc = new JScrollPane(loa);
				lojsc.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
				loa.setBorder(BorderFactory.createTitledBorder("对局详情"));
				loa.append("目前已经保存的对局: " + "\n");
				for (int i = 0; i < a; i = i + 1) {
					loa.append("对局" + Integer.toString(i + 1) + "\n");
					loa.paintImmediately(loa.getBounds());
				}
				JPanel lojp = new JPanel();
				JLabel lojl = new JLabel("请输入需要加载的对局的数字：");
				JTextField lojf = new JTextField(6);
				JButton lob = new JButton("确认");
				lojp.add(lojl);
				lojp.add(lojf);
				lojp.add(lob);
				lo.add(lojsc, BorderLayout.NORTH);
				lo.add(lojp, BorderLayout.SOUTH);
				lo.pack();
				lo.setLocationRelativeTo(null);// 居中显示
				lo.setVisible(true);// 设置为可见
				lob.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						oop = Integer.parseInt(lojf.getText());
						// 加载
						String filePath = "res/save/" + Integer.toString(oop) + ".txt";
						chessbord.restart();
						FileInputStream fin = null;
						try {
							fin = new FileInputStream(filePath);
						} catch (FileNotFoundException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
						InputStreamReader reader = new InputStreamReader(fin);
						BufferedReader buffReader = new BufferedReader(reader);
						String strTmp = "";
						try {
							while ((strTmp = buffReader.readLine()) != null) {
								chessbord.loadchess(strTmp);
							}
						} catch (IOException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
						try {
							buffReader.close();
						} catch (IOException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
						lo.setVisible(false);
					}
				});
			} else if (obj == rep) {
				new replay();
				ChessBord.GameOver = true;
			} else if (obj == seeg) {
				JFrame spf = new JFrame();
				spf.setLayout(new BorderLayout());
				JPanel ppp = new JPanel();
				JLabel jlp = new JLabel("请输入您的观战服务器端口");
				JTextField jll = new JTextField(5);
				JButton jbb = new JButton("确认");
				ppp.add(jlp);
				ppp.add(jll);
				spf.add(ppp, BorderLayout.NORTH);
				spf.add(jbb, BorderLayout.SOUTH);
				spf.pack();
				spf.setVisible(true);
				jbb.addActionListener(new ActionListener() {

					public void actionPerformed(ActionEvent e) {
						// 作为主机
						seeis = 1;
						new Thread() {
							public void run() {
								spf.setVisible(false);
								try {
									seesp = new ServerSocket(Integer.parseInt(jll.getText()));
								} catch (NumberFormatException | IOException e1) {
									// TODO Auto-generated catch block
									e1.printStackTrace();
								}
								try {
									seetcp = seesp.accept();
								} catch (IOException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							};
						}.start();
					}
				});

			}
		}
	}

	public static void main(String[] args) throws FileNotFoundException, JavaLayerException {
		ChessJFrame jf = new ChessJFrame();// 声明框架对象
		jf.setLocationRelativeTo(null);// 居中显示
		jf.setVisible(true);// 设置为可见

		//
		JFrame staa = new JFrame();
		staa.setLocationRelativeTo(null);// 居中显示
		staa.setLayout(new GridLayout(2, 1));
		JLabel jl1 = new JLabel("    请选择您的主机类型");
		JPanel jp1 = new JPanel();
		JButton bb1 = new JButton("主机");
		JButton bb2 = new JButton("客户端");
		JButton bbs = new JButton("观战方");
		JButton bb3 = new JButton("确认");
		JButton bb4 = new JButton("确认");
		JButton bb5 = new JButton("确认");
		jp1.add(bb1);
		jp1.add(bb2);
		jp1.add(bbs);
		staa.add(jl1);
		staa.add(jp1);
		staa.pack();
		staa.setVisible(true);

		bb1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 作为主机
				jl1.setText("      输入您的端口");
				jp1.remove(bb2);
				jp1.remove(bb1);
				jp1.remove(bbs);
				jtf1 = new JTextField(5);
				jp1.add(jtf1);
				jp1.add(bb3);
				jp1.repaint();
				tse = 1;
			}
		});
		JFrame staf = new JFrame();
		bb2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 作为客户端
				staa.setVisible(false);
				staf.setLayout(new GridLayout(3, 1));
				jl1.setText("      输入您要连接的IP");
				jp1.remove(bb2);
				jp1.remove(bb1);
				jp1.remove(bbs);
				jtf1 = new JTextField(14);
				jp1.add(jl1);
				jp1.add(jtf1);
				jp1.repaint();
				JPanel jp2 = new JPanel();
				JLabel jl2 = new JLabel("    输入您要连接的IP的端口");
				jtf2 = new JTextField(10);
				jp2.add(jl2);
				jp2.add(jtf2);
				staf.add(jp1);
				staf.add(jp2);
				staf.add(bb4);
				staf.setLocationRelativeTo(null);// 居中显示
				staf.pack();
				staf.setVisible(true);
				tse = 2;
			}
		});

		bbs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 作为观战
				staa.setVisible(false);
				staf.setLayout(new GridLayout(3, 1));
				jl1.setText("      输入您要连接的IP");
				jp1.remove(bb2);
				jp1.remove(bb1);
				jp1.remove(bbs);
				jtf1 = new JTextField(14);
				jp1.add(jl1);
				jp1.add(jtf1);
				jp1.repaint();
				JPanel jp2 = new JPanel();
				JLabel jl2 = new JLabel("    输入您要连接的IP的端口");
				jtf2 = new JTextField(10);
				jp2.add(jl2);
				jp2.add(jtf2);
				staf.add(jp1);
				staf.add(jp2);
				staf.add(bb5);
				staf.setLocationRelativeTo(null);// 居中显示
				staf.pack();
				staf.setVisible(true);
			}
		});

		bb5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 作为观战
				seeTcp.dk = Integer.parseInt(jtf2.getText());
				seeTcp.ip = jtf1.getText();
				staa.setVisible(false);
				try {
					setcp = new seeTcp(jf);
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});

		bb3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 开始连接
				SeverTcp.dk = Integer.parseInt(jtf1.getText());
				staa.setVisible(false);
				try {
					stcp = new SeverTcp(jf);
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});

		bb4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 开始连接
				ClientTcp.dk = Integer.parseInt(jtf2.getText());
				ClientTcp.ip = jtf1.getText();
				staa.setVisible(false);
				try {
					ctcp = new ClientTcp(jf);
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				staf.setVisible(false);
			}
		});
		// 添加背景音乐

		//

	}

	public static void writeTxt(String txtPath, Chess[] chesslist) {
		FileOutputStream fileOutputStream = null;
		File file = new File(txtPath);
		try {
			if (file.exists()) {
				// 判断文件是否存在，如果不存在就新建一个txt
				file.createNewFile();
			}
			fileOutputStream = new FileOutputStream(file);
			for (int i = 0; i < chessbord.chessCount; i = i + 1) {
				String a = "";
				a = a + Integer.toString(chesslist[i].getX()) + "," + Integer.toString(chesslist[i].getY()) + "\n";
				fileOutputStream.write(a.getBytes());
				fileOutputStream.flush();
			}
			fileOutputStream.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void writenub(String txtPath, String content) {
		File file = new File(txtPath);
		try {
			if (file.exists()) {
				// 判断文件是否存在，如果不存在就新建一个txt
				file.createNewFile();
			}
			FileWriter fileWriter = new FileWriter(file);
			fileWriter.write(content); // 写入空
			fileWriter.flush();
			fileWriter.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
