package filter;

import java.io.IOException;
import java.lang.reflect.Method;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import beans.Auth;

import dbaccess.DB;

import utility.Util;

/**
 * Servlet Filter implementation class BoardFilter
 */
@WebFilter("/BoardFilter")
public class BoardFilter implements Filter {

    /**
     * Default constructor. 
     */
    public BoardFilter() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	//precondition : 유저가 로그인 상태임	
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		HttpServletRequest req = (HttpServletRequest)request;
		HttpSession session = req.getSession();
		String role = (String)session.getAttribute("role");
		String boardName = req.getParameter("boardName");
		
		DB db = DB.getInstance();
		Auth boardAuth = db.dbBoard.getBoardAuth(boardName);		
		
		//접근하려는 게시판에 대한 접근 권한 정보를 얻어온다.
		String authString = "";
		try
		{
			//첫글자를 대문자로 바꾼다.
			role = role.substring(0,1).toUpperCase() + role.substring(1);
			Method getMethod = Auth.class.getMethod("get"+role, null);
			authString = (String)getMethod.invoke(boardAuth, (Object[])null);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}		
		
		request.setAttribute("canRead", false);
		request.setAttribute("canWrite", false);
		request.setAttribute("canAdmin", false);
		
		char[] auth = authString.toCharArray();
		//auth[0],auth[1],auth[2] 는 차례로 read,write,admin 권한을 의미
		if(auth[0]!='-')
			request.setAttribute("canRead", true);
		if(auth[1]!='-')
			request.setAttribute("canWrite", true);
		if(auth[2]!='-')
			request.setAttribute("canAdmin", true);		
		
		chain.doFilter(request, response);
	}

	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		// TODO Auto-generated method stub
	}
}
