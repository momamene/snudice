package servletBoard;

import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.ArticleInfo;
import dbaccess.DB;

/**
 * Servlet implementation class articleModifyComplete
 */
@WebServlet("/articleModifyComplete")
public class ArticleModifyComplete extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
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
		int articleIndex=Integer.parseInt( request.getParameter("articleIndex"));
		article.setArticleIndex(articleIndex);
		System.out.println("article info is " + article.toString());
		System.out.println(" text is" + request.getParameter("content"));
		DB db = DB.getInstance();
		int result = db.dbBoard.updateArticle(article);
		if(result ==0)
			System.out.println("아마 실패한듯 요 업데이트 병신 새끼");
        String nextPage = "board/writeModifySuccess.jsp";
        request.setAttribute("WriteModify", "modify");
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
	}
}
