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

import utility.Util;

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
		
		request.setCharacterEncoding("utf-8");
		
		String boardName = (String) session.getAttribute("boardName");
		String userId = (String)session.getAttribute("userId");
		String title = request.getParameter("title");
		String content = request.getParameter("content");		
		
		if(title.compareTo("")==0)
			title = Util.currDateTime() + " 에 작성한 글입니다.";
		
		ArticleInfo article = new ArticleInfo(boardName,userId,title,content);		
		
		DB db = DB.getInstance();
		int articleIndex = db.dbBoard.insertArticle(article);		
		 
        String nextPage = "articleView.do?articleIndex="+articleIndex;
        session.setAttribute("articleIndex",articleIndex );
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
	}
}
