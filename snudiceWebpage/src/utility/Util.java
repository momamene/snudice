package utility;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;

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
	
	//모든 인자를 출력한다.
	public static void printAllParams(HttpServletRequest request)
	{
		Enumeration<String> e = request.getParameterNames();
		while(e.hasMoreElements())
		{
			String paramName = e.nextElement();
			System.out.println(paramName+"="+request.getParameter(paramName));		
		}
	}
}
