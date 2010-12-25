package servletAccount;

import java.io.IOException;
import java.util.Random;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import beans.UserInfo;
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
		
		UserInfo userInformation = new UserInfo(userId,password);
		request.setAttribute("userInfo", userInformation);
		
		String nextPage = "joinSuccess.jsp";
		
		DB db = DB.getInstance();
		boolean isExistingUser = db.dbAccount.isExistingUser(userId);
		if(isExistingUser)
			nextPage = "joinFailed.jsp";
		else //신규가입 처리
		{			
			//계정 추가
			db.dbAccount.insertNewUser(userId,password);			
		}
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);
	}
}
