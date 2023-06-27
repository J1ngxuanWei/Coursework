package five;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;

public class replay {
	ChessBord chessbd;
	static int nub = 0;
	JButton b1;
	JButton b2;
	int oop;
	int strb = 0;

	public replay() {
		chessbd = new ChessBord();
		chessbd.replay = true;
		JFrame re = new JFrame();
		re.setTitle("五子棋复盘");// 设置标题
		re.setLayout(new BorderLayout());
		re.setResizable(false);
		MyButtonLister mb = new MyButtonLister();// 按钮事件处理对象
		JPanel tool = new JPanel();// 面板对象
		tool.setLayout(new FlowLayout(FlowLayout.CENTER));// 流式布局
		b1 = new JButton("上一步");
		b2 = new JButton("下一步");
		tool.add(b1);
		tool.add(b2);
		b1.addActionListener(mb);
		b2.addActionListener(mb);
		re.add(tool, BorderLayout.SOUTH);// 按钮所在的位置
		re.add(chessbd, BorderLayout.CENTER);// 添加棋盘对象
		re.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 设置关闭
		re.pack();
		// 获得复盘数字
		JFrame lo = new JFrame();
		lo.setLayout(new BorderLayout());
		JTextArea loa = new JTextArea(5, 6);
		JScrollPane lojsc = new JScrollPane(loa);
		lojsc.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		loa.setBorder(BorderFactory.createTitledBorder("对局详情"));
		loa.append("目前已经保存的对局: " + "\n");
		for (int i = 0; i < ChessJFrame.a; i = i + 1) {
			loa.append("对局" + Integer.toString(i + 1) + "\n");
			loa.paintImmediately(loa.getBounds());
		}
		JPanel lojp = new JPanel();
		JLabel lojl = new JLabel("请输入需要复盘的对局的数字：");
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
		//
		lob.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				oop = Integer.parseInt(lojf.getText());
				lo.setVisible(false);
			}
		});
		//
		//
		re.setVisible(true);

	}

	private class MyButtonLister implements ActionListener {
		// 按钮处理事件类
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			Object obj = e.getSource();// 获取事件源
			if (obj == b1) {// 事件源是上一步按钮
				// 上一步
				strb = strb - 1;
				chessbd.goback();
			} else if (obj == b2) {// 事件源是下一步按钮
				// 下一步
				String filePath = "res/save/" + Integer.toString(oop) + ".txt";
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
				for (int i = 0; i < strb; i = i + 1) {
					try {
						buffReader.readLine();
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
				try {
					if ((strTmp = buffReader.readLine()) != null) {
						strb = strb + 1;
						chessbd.nextchess(strTmp);
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
			}
		}
	}

}
