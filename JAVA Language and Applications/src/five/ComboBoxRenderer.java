package five;

import java.awt.Component;
import java.awt.Image;
import java.util.HashMap;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;

class ComboBoxRenderer extends JLabel implements ListCellRenderer<Object> {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	// 准备 一个map，用于保存提前准备好的图片
	public HashMap<String, Icon> icons = new HashMap<>();

	public ComboBoxRenderer() {// 构造函数
		setOpaque(true); // 设置透明
		// setHorizontalAlignment(CENTER);//设置本标签水平居中对齐
		// setVerticalAlignment(CENTER);//设置本标签垂直居中对齐
		this.setSize(50, 50);

		// 修改图片尺寸，使其填满
		ImageIcon i0 = new ImageIcon("res/0.jpg");
		i0.getImage();
		Image temp0 = i0.getImage().getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_DEFAULT);
		i0 = new ImageIcon(temp0);

		ImageIcon i1 = new ImageIcon("res/1.jpg");
		i1.getImage();
		Image temp1 = i1.getImage().getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_DEFAULT);
		i1 = new ImageIcon(temp1);

		ImageIcon i2 = new ImageIcon("res/2.jpg");
		i2.getImage();
		Image temp2 = i2.getImage().getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_DEFAULT);
		i2 = new ImageIcon(temp2);

		ImageIcon i3 = new ImageIcon("res/3.jpg");
		i3.getImage();
		Image temp3 = i3.getImage().getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_DEFAULT);
		i3 = new ImageIcon(temp3);

		ImageIcon i4 = new ImageIcon("res/4.jpg");
		i4.getImage();
		Image temp4 = i4.getImage().getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_DEFAULT);
		i4 = new ImageIcon(temp4);

		icons.put("无", i0);// 在map中放入提前准备好图片
		icons.put("1", i1);// 在map中放入提前准备好图片
		icons.put("2", i2); // 用对象作为索引
		icons.put("3", i3); // 用对象作为索引
		icons.put("4", i4); // 用对象作为索引
	}

	public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected,
			boolean cellHasFocus) {

		String color = (String) value;
		setIcon(icons.get(color));

		return this;

	}

}