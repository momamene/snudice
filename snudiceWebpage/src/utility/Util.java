package utility;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class Util {
	public static String currDateTime() {
		Date today = new Date();	
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		return dateFormat.format(today);
	}
	
	public static String encodeHtml(String html) {
		StringBuffer result = new StringBuffer();
		
		for(int i=0;i<html.length();i++)
		{
			char c = html.charAt(i);
			if(c>127 || c=='"' || c=='<' || c=='>')
				result.append("&#"+(int)c+";");
			else if(c=='\t')
				result.append("&nbsp;&nbsp;&nbsp;&nbsp;");
			else if(c=='\n')
				result.append("<br/>");
			else if(c==' ')
				result.append("&nbsp;");
			else
				result.append(c);
		}
		return result.toString();
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
	
	//servlet context 의 속성을 얻는다
	public static Object getServletContextAttr(HttpServletRequest request,String attrName) {
		ServletContext sc = request.getServletContext();
		return sc.getAttribute(attrName);
	}
}
