package servletBoard;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;



import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.ArticleInfo;
import dbaccess.DB;

/**
 * Servlet implementation class ArticleWrite
 */
@WebServlet("/ArticleWrite")
public class ArticleWrite extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleWrite() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session = request.getSession(); 
		String boardName = (String) session.getAttribute("boardName");
		Calendar cal = Calendar.getInstance();
		cal.getTime();
		 
		Date today = new Date();
		
		request.setCharacterEncoding("utf-8");
		
		System.out.println(today.toString());
		System.out.println("boardName is " + boardName);
		ArticleInfo article = new ArticleInfo(boardName,
				(String) session.getAttribute("userId"),
				request.getParameter("title"), request.getParameter("content"),
				today);
		System.out.println("article info is " + article.toString());
		System.out.println(" text is" + request.getParameter("content"));
		DB db = DB.getInstance();
		int articleIndex = db.dbBoard.insertArticle(article);
		System.out.println("article index is "+ articleIndex);
		//성공하면 성공 알림 -> 리스트 보기. 실패하면 즐        
        String nextPage = "board/writeModifySuccess.jsp";  
        session.setAttribute("articleIndex",articleIndex );
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
	}
}
