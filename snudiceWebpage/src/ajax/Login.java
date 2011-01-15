package ajax;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.Encrypt;

import constant.Const;

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

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String userId = request.getParameter("userId");
		String password = request.getParameter("password");	
		
		//길면 자른다.
		if(userId.length()>Const.userIdMaxLen)
			userId = userId.substring(0, Const.userIdMaxLen);
		if(password.length()>Const.passwordMaxLen)
			password = password.substring(0,Const.passwordMaxLen);
		
		ServletOutputStream os = response.getOutputStream();
		
		HttpSession session = request.getSession();	
		String sessionUserId = (String)session.getAttribute("userId");
		
		//이미 로그인 된 경우
		if(sessionUserId!=null && sessionUserId.compareTo(userId)==0)
		{
			os.print("alreadyLoggined");
			return;
		}
		
		DB db = DB.getInstance();
		boolean isExistingUser = db.dbAccount.isValidUser(userId,Encrypt.md5(password));
		if(!isExistingUser)		
			os.print("loginFail");		
		else
		{
			//session에 userId를 속성으로 지정					
			session.setAttribute("userId", userId);	
			
			//secure login	
			request.login(userId, password);
			
			os.print("loginOK");
		}		
	}
}
