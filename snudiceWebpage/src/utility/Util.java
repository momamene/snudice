package utility;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;
import java.util.Random;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import constant.Const;

public class Util {
	//리셋된 password를 리턴. (Const.newPwDigits 자리수 만큼의 10진수)
	public static String getNewPw() {
		Random rand = new Random(System.currentTimeMillis());
		StringBuffer sb = new StringBuffer();
		for(int i=0;i<Const.newPwDigits;i++)
			sb.append(rand.nextInt(10));
		
		return sb.toString();
	}
	
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
	
	//String의 byte수를 계산한다. 아스키코드 값이 128이상인 것은 2바이트로 취급한다.
	public static int getByteCnt(String s) {
		int result = 0;
		for(int i=0;i<s.length();i++)
		{
			if(s.charAt(i)<128)
				result += 1;
			else
				result += 2;
		}
		return result;
	}

	//email 인증에 사용할 activation code를 만든다.
	public static String getActivationCode() {
		Random r = new Random(System.currentTimeMillis());		
		return Encrypt.md5(Long.toString(r.nextLong()));		
	}

	//datetime string을 간략화 한다.
	//input은 2011-03-03 17:39:29.0 의 형태라고 가정한다.
	//output은 03-03 17:39 의 형태가 된다.
	public static String getSimpleDateTime(String dateTime) {
		return dateTime.substring(5,dateTime.length()-5);		
	}
}
