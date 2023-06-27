package five;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class chatview extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	static int paintnub;
	static JLabel lk;

	chatview() {
		super();
		paintnub = 0;
		this.setLayout(null);
		this.setSize(400, 200);
	}

	void changep(int a) {
		paintnub = a;
		repaint();
	}

	public void paintComponent(Graphics g) {
		super.paintComponents(g);
		g.setColor(Color.WHITE);
		g.fillRect(5, 18, 221, 181);
		g.setColor(Color.BLACK);
		if (paintnub == 0)
			return;
		ImageIcon ic1 = new ImageIcon("res/1.jpg");
		ImageIcon ic2 = new ImageIcon("res/2.jpg");
		ImageIcon ic3 = new ImageIcon("res/3.jpg");
		ImageIcon ic4 = new ImageIcon("res/4.jpg");
		ImageIcon ic = null;
		if (paintnub == 1) {
			ic = ic1;
		} else if (paintnub == 2) {
			ic = ic2;
		} else if (paintnub == 3) {
			ic = ic3;
		} else if (paintnub == 4) {
			ic = ic4;
		}
		Image d = ic.getImage();
		Font ft = new Font("黑体", Font.BOLD, 18);
		g.drawImage(d, 40, 50, 150, 150, this);
		g.drawRect(5, 18, 221, 181);
		g.setFont(ft);
		g.drawString("对方向您发送了", 53, 39);

	}

}
