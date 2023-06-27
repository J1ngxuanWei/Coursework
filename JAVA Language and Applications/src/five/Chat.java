package five;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;

public class Chat extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	static Vector<String> fname = new Vector<String>();
	static JTextArea a1;
	static JTextArea a2;
	static JComboBox<?> c1;
	static JComboBox<String> c2;
	static JButton b1;
	static JTextArea a3;
	static JPanel ca;
	static chatview ct;
	static JScrollPane jsc1;
	static JScrollPane jsc2;

	static String bq;
	static String yy;

	public Chat(ChessJFrame af) {
		bq = "0";
		yy = "无";
		this.setLayout(new BorderLayout());
		this.setSize(500, 600);
		// 公告栏
		JPanel gonggao = new JPanel();
		gonggao.setBorder(BorderFactory.createTitledBorder("公告"));
		a1 = new JTextArea(11, 20);
		jsc2 = new JScrollPane(a1);
		jsc2.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		gonggao.setLayout(new GridLayout(1, 1));
		gonggao.add(jsc2);
		// 聊天栏
		//
		ca = new JPanel();
		ct = new chatview();

		ca.setBorder(BorderFactory.createTitledBorder("聊天"));
		ca.setLayout(new BorderLayout());
		a2 = new JTextArea(12, 20);
		jsc1 = new JScrollPane(a2);
		jsc1.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		ca.add(jsc1, BorderLayout.NORTH);
		//
		JPanel ctool = new JPanel();
		ctool.setLayout(new BorderLayout());
		JPanel ctt = new JPanel();
		ctt.setLayout(new BorderLayout());
		JPanel ctt1 = new JPanel();
		ctt1.setLayout(new FlowLayout(0));
		JLabel l1 = new JLabel("表情    ");
		//
		String[] stri = { "无", "1", "2", "3", "4" };
		c1 = new JComboBox<Object>(stri);
		ComboBoxRenderer renderer = new ComboBoxRenderer(); // 一个自定义的能显示定制内容的组件
		renderer.setPreferredSize(new Dimension(50, 50));// 设置最佳尺寸
		c1.setRenderer(renderer);// 让渲染组件起作用
		c1.setMaximumRowCount(5);// 设置最大显示多少行

		ActionListener listener = new ActionListener() { // 定义一个动作监听器匿名内部类对象
			public void actionPerformed(ActionEvent e) {
				JComboBox<?> cb = (JComboBox<?>) e.getSource(); // 获得发生事件的组合框对象
				String sstr = (String) cb.getSelectedItem();
				bq = sstr;
			}
		};
		c1.addActionListener(listener);// 将监听器注册到组合框上

		//
		ctt1.add(l1);
		ctt1.add(c1);
		JPanel ctt2 = new JPanel();
		ctt2.setLayout(new FlowLayout(0));
		JLabel l2 = new JLabel("语音包");
		c2 = new JComboBox<String>();
		this.setf();
		c2.addItem("无");
		ctt2.add(l2);
		ctt2.add(c2);
		b1 = new JButton("发送");
		ctt.add(ctt1, BorderLayout.NORTH);
		ctt.add(ctt2, BorderLayout.SOUTH);
		ctool.add(ctt, BorderLayout.CENTER);
		ctool.add(b1, BorderLayout.EAST);
		ca.add(ctool, BorderLayout.CENTER);
		//
		a3 = new JTextArea(6, 1);
		ca.add(a3, BorderLayout.SOUTH);

		add(gonggao, BorderLayout.NORTH);
		add(ca, BorderLayout.CENTER);
		Chat.a3.setText("空");
		//
		c2.addItemListener((ItemListener) new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				if (ItemEvent.SELECTED == event.getStateChange()) {
					String cb = (String) c2.getSelectedItem();
					yy = cb;
					System.out.println(yy);
				}
			}
		});

	}

	void setf() {
		c2.addItem("哎说句话好吗");
		c2.addItem("哎呀蠢得一匹");
		c2.addItem("拜拜");
		c2.addItem("不急慢慢来");
		c2.addItem("不能着急");
		c2.addItem("得得得得得得得");
		c2.addItem("诶呀好怕啊");
		c2.addItem("诶哟");
		c2.addItem("搞笑吗你在");
		c2.addItem("不跟你多比比");
		c2.addItem("嗯继续继续继续");
		c2.addItem("你别停");
		c2.addItem("你个弱智");
		c2.addItem("你好");
		c2.addItem("你说话大声点");
		c2.addItem("你这输了呀");
		c2.addItem("牛逼继续来");
		c2.addItem("忍一手风平浪静");
		c2.addItem("你不能这样");
		c2.addItem("尴尬了一秒钟");
		c2.addItem("说实话很尴尬");
		c2.addItem("听得见我说话吗");
		c2.addItem("玩游戏一定要笑");
		c2.addItem("我错了对不起");
		c2.addItem("我很他妈强");
		c2.addItem("给年轻人机会");
		c2.addItem("我是吓大的");
		c2.addItem("我一点都不怕");
		c2.addItem("不知道输怎么写");
		c2.addItem("小脾气还挺臭的");
		c2.addItem("一耳光打死我");
		c2.addItem("用力点");
		c2.addItem("有点恶心人了呀");
	}

}
