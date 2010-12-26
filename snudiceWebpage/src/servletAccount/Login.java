package servletAccount;

import java.io.*;
import java.util.List;

import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.Encrypt;

import dbaccess.DB;

import beans.UserInfo;

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
    
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String userId = request.getParameter("userId");
		String password = request.getParameter("password");			
		
		UserInfo userInformation = new UserInfo(userId,password,null);
		request.setAttribute("userInfo", userInformation);
		
		String nextPage = "loginSuccess.jsp";
		
		DB db = DB.getInstance();
		boolean isExistingUser = db.dbAccount.isValidUser(userId,Encrypt.encrypt(password));
		if(!isExistingUser)
			nextPage = "loginFailed.jsp";
		
		else
		{
			//session에 userId를 속성으로 지정
			HttpSession session = request.getSession();	
			session.setMaxInactiveInterval(3600);
			session.setAttribute("userId", userId);			
		}
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);
	}
}