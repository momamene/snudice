package ajax;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.User;

import dbaccess.DB;

import utility.Encrypt;

/**
 * Servlet implementation class InfoModify
 */
@WebServlet("/InfoModify")
public class InfoModify extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public InfoModify() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		ServletOutputStream os = response.getOutputStream();
		
		HttpSession session = request.getSession();
		String userId = (String)session.getAttribute("userId");				
		String pastPw = request.getParameter("pastPw");
		
		DB db = DB.getInstance();		
		
		boolean validUser = db.dbAccount.isValidUser(userId, Encrypt.md5(pastPw));
		if(!validUser)
		{
			os.print("error");
			return;
		}
		
		String newPw = request.getParameter("newPw");		
		String newEmail = request.getParameter("newEmail");
		String newComment = request.getParameter("newComment");
		
		User user = db.dbAccount.getUser(userId);
		user.setComment(newComment);
		user.setEmail(newEmail);
		if(newPw!=null) //password가 비어있으면 변경하지 않음
			user.setPassword(Encrypt.md5(newPw));		
		db.dbAccount.setUser(user);
		
		os.print("modifyOK");
	}
}
