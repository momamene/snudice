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

import constant.Const;

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
		
		if(session.getAttribute("root")==null)
		{
			synchronized(session)
			{
				session.setAttribute("root",Const.root); //root 경로 설정
			}
		}
		
		StringBuffer log = new StringBuffer("["+Util.currDateTime()+"]");
		log.append(" from "+"<"+req.getRemoteAddr()+">");
		if(req.getRemoteUser()!=null)
		{
			log.append(" user="+"<"+req.getRemoteUser()+">");
			if(session.getAttribute("userId")==null)
			{
				synchronized(session)
				{
					session.setAttribute("userId", req.getRemoteUser()); //userId 설정
				}
			}				
		}
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
