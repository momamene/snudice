package servletAccount;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import utility.Util;

import beans.User;

import dbaccess.DB;

/**
 * Servlet implementation class AccountActivate
 */
@WebServlet("/AccountActivate")
public class AccountActivate extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AccountActivate() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {		
		String userId = request.getParameter("userId");
		String activationCode = request.getParameter("code");
		DB db = DB.getInstance();
		try
		{
			if(userId==null || activationCode==null)
				throw new RuntimeException();
			
			User user = db.dbAccount.getNotActivatedUser(userId, activationCode);
			user.setRecentConnect(Util.currDateTime());
			db.dbAccount.deleteNotActivatedUser(user.getUserId());
			db.dbAccount.insertNewUser(user);
			
			//rank table에 추가
			db.dbGame.addRank(user.getNickname());
			
			response.setContentType("text/plain; charset=UTF-8");
			response.setCharacterEncoding("UTF-8");
			PrintWriter pw = response.getWriter();
			pw.print("계정이 활성화되었습니다.");				
		}
		catch(RuntimeException re)
		{
			String nextPage = "/error.jsp";	
			RequestDispatcher view = request.getRequestDispatcher(nextPage);
			view.forward(request, response);			
		}		
	}
}
