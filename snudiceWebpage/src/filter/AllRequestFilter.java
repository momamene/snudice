package filter;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import utility.Util;

import dbaccess.DB;

/**
 * Servlet Filter implementation class AllRequestFilter
 */
@WebFilter("/AllRequestFilter")
public class AllRequestFilter implements Filter {

    /**
     * Default constructor. 
     */
    public AllRequestFilter() {
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
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		request.setCharacterEncoding("utf-8");
		
		HttpServletRequest req = (HttpServletRequest)request;
		HttpSession session = req.getSession();
		session.setMaxInactiveInterval(1800);
		DB db = DB.getInstance();
		
		StringBuffer log = new StringBuffer("["+Util.currDateTime()+"]");
		log.append(" from "+"<"+req.getRemoteAddr()+">");
		if(req.getRemoteUser()!=null) //로그인 된 경우
		{			
			if(session.getAttribute("nickname")==null)
			{
				synchronized(session)
				{
					String userId = req.getRemoteUser();
					String nickname = db.dbAccount.getNickname(userId);
					session.setAttribute("userId", userId); //userId 설정
					session.setAttribute("nickname", nickname); //nickname 설정					
				}
			}
			if(session.getAttribute("role")==null)
			{
				synchronized(session)
				{					
					String role = db.dbAccount.getUserRole(req.getRemoteUser()); //role 설정
					session.setAttribute("role", role);
				}				
			}
			log.append(" user="+"<"+req.getRemoteUser()+":"+session.getAttribute("role")+">");
		}		
		else //로그인 안된 경우
		{
			if(session.getAttribute("userId")!=null)
			{
				synchronized(session)
				{
					session.removeAttribute("userId");					
				}				
			}
			if(session.getAttribute("nickname")!=null)
			{
				synchronized(session)
				{
					session.removeAttribute("nickname");					
				}				
			}
			if(session.getAttribute("role")!=null)
			{
				synchronized(session)
				{
					session.removeAttribute("role");
				}
			}
		}
		
		//log.append(" "+req.getHeader("User-Agent"));
		
		if(req.isSecure())
			log.append(" (HTTPS)");
		else
			log.append(" (HTTP)");
		log.append(" "+req.getMethod());	
		log.append(" "+req.getServletPath());
		
		System.out.println(log);
		
		chain.doFilter(request, response);		
	}

	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		// TODO Auto-generated method stub
	}

}
