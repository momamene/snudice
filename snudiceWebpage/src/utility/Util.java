package utility;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

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
	public static void printAllParams(HttpServletRequest request){
		Enumeration<String> e = request.getParameterNames();
		while(e.hasMoreElements())
		{
			String paramName = e.nextElement();
			System.out.println("[param] "+paramName+"=["+request.getParameter(paramName)+"]");		
		}
	}
	
	//세션의 속성을 출력한다.
	public static void printAllSessionAttr(HttpServletRequest request) {
		HttpSession session = request.getSession();
		Enumeration<String> e = session.getAttributeNames();
		while(e.hasMoreElements())
		{
			String attrName = e.nextElement();
			System.out.println("[session] "+attrName+"=["+session.getAttribute(attrName)+"]");		
		}
	}
	
	//request 객체의 모든 속성을 출력한다.
	public static void printAllRequestAttr(HttpServletRequest request) {
		Enumeration<String> e = request.getAttributeNames();
		while(e.hasMoreElements())
		{
			String attrName = e.nextElement();
			System.out.println("[req] "+attrName+"=["+request.getAttribute(attrName)+"]");		
		}
	}
}
