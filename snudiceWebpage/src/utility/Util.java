package utility;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Util {
	public static String currDateTime() {
		Date today = new Date();	
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		return dateFormat.format(today);
	}
}
