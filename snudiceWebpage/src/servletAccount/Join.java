package servletAccount;

import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import dbaccess.DB;

/**
 * Servlet implementation class Join
 */
@WebServlet("/Join")
public class Join extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Join() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		
		String userId = request.getParameter("userId");
		String password = request.getParameter("password");		
		String email = request.getParameter("email");
		
		String nextPage = "joinFailed.jsp";
		String msg = "";
				
		if(userId.compareTo("")==0 || password.compareTo("")==0 || email.compareTo("")==0)
			msg = "모든 항목을 채워주세요!";		
		else if(userId.length()>16)
			msg = "id는 16자까지만 가능합니다.";
		else
		{
			DB db = DB.getInstance();
			boolean isExistingUser = db.dbAccount.isExistingUser(userId);
			boolean isExistingEmail = db.dbAccount.isExistingEmail(email);
			if(isExistingUser)
				msg = "이미 존재하는 id 입니다.";
			else if(isExistingEmail)
				msg = "이미 존재하는 email 입니다.";
			else
			{
				nextPage = "joinSuccess.jsp";
				//계정 추가
				db.dbAccount.insertNewUser(userId,password,email);	
			}			
		}
		
		request.setAttribute("message", msg);
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);
	}
}
