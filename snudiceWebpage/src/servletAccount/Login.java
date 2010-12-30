package servletAccount;

import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import dbaccess.DB;

/**
 * Servlet implementation class Login
 */
@WebServlet("/Login")
public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Login() {
        super();
        // TODO Auto-generated constructor stub
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	doPost(request,response);
    }
    
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {		
		String userId = request.getParameter("userId");
		String password = request.getParameter("password");		
		
		String nextPage = "loginSuccess.jsp";
		
		DB db = DB.getInstance();
		boolean isExistingUser = db.dbAccount.isValidUser(userId,password);
		if(!isExistingUser)
			nextPage = "loginFailed.jsp";		
		else
		{
			//session에 userId를 속성으로 지정
			HttpSession session = request.getSession();			
			session.setAttribute("userId", userId);	
			
			//secure login			
			request.login(userId, password);
			
			//로그인 뒤 다른 곳으로 가야 하는 경우(ex-로그인 하지 않고 링크를 통해 글을 보려고 시도한 경우)
			String redirectUrl = (String)session.getAttribute("redirectUrl");			
				
			if(redirectUrl!=null)
			{				
				session.removeAttribute("redirectUrl");
				response.sendRedirect(redirectUrl);
				return;
			}
			
			//게시판 목록을 가져온다.
			request.setAttribute("boardList", db.dbBoard.getBoardList());
		}		
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);
	}
}