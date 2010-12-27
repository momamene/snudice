package utility;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Util {
	public static String currDateTime() {
		Date today = new Date();	
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		return dateFormat.format(today);
	}
	
	public static String toHtml(String str) {
		String result = null;
		result = str.replace("<", "&lt;");
		result = result.replace(">", "&gt");
		result = result.replace("\n", "<br/>");
		result = result.replace(" ", "&nbsp;");
		result = result.replace("(", "&#40;");
		result = result.replace(")", "&#41;");
		return result;
	}	
}
