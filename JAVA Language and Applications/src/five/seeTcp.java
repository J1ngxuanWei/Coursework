package five;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class seeTcp {
	static int dk;
	static String ip;
	static Socket s;
	static int issee = 0;

	seeTcp(ChessJFrame cjf) throws Exception, IOException {
		ChessBord.GameStart = true;
		issee = 1;
		s = new Socket(ip, dk);
		BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
		Chat.a1.append("连接观战服务器成功！" + "\n");
		Chat.a1.paintImmediately(Chat.a1.getBounds());

		// 接受
		new Thread() {
			public void run() {
				String line = null;
				try {
					while ((line = in.readLine()) != null) {
						int pl = line.charAt(0) - 48;
						line = line.substring(2);
						if (pl == 1) {
							// 下棋
							int xx;
							int yy;
							xx = getxx(line);
							yy = getyy(line);
							Chat.a1.append("一方下棋" + "\n");
							Chat.a1.paintImmediately(Chat.a1.getBounds());
							ChessJFrame.chessbord.pickchess(xx, yy);
						}
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			};
		}.start();
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
