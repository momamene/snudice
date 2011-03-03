package ajax;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.google.gson.Gson;

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
		
		HttpSession session = request.getSession();	
		String sessionUserId = (String)session.getAttribute("userId");		
		
		HashMap<String,String> respData = new HashMap<String,String>();	
		
		//이미 로그인 된 경우
		if(sessionUserId!=null)		
			respData.put("msg","alreadyLoggined");
		else
		{
			DB db = DB.getInstance();
			boolean isExistingUser = db.dbAccount.isValidUser(userId,Encrypt.md5(password));
			if(!isExistingUser)		
				respData.put("msg", "loginFail");		
			else
			{
				String nickname = db.dbAccount.getNickname(userId);
				String role = db.dbAccount.getUserRole(userId);			
						
				session.setAttribute("userId", userId);	
				session.setAttribute("nickname", nickname);
				session.setAttribute("role", role);			
				
				//secure login				
				request.login(userId, password);	
				
				respData.put("msg", "loginOK");
				respData.put("userId", userId);
				respData.put("role", role);
			}		
		}		
		
		Gson gson = new Gson();
		String json = gson.toJson(respData);
		PrintWriter pw = response.getWriter();
		pw.print(json);	
	}
}
