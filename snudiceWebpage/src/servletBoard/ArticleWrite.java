package servletBoard;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.Util;

import beans.Article;
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
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session = request.getSession();
		
		String userId = (String)session.getAttribute("userId");
		String boardName = request.getParameter("boardName");		
		String title = request.getParameter("title");
		String content = request.getParameter("content");
		String currPage = request.getParameter("currPage");			
		
		if(title.compareTo("")==0)
			title = Util.currDateTime() + " 에 작성한 글입니다.";
		
		Article article = new Article(boardName,userId,title,content);		
		
		DB db = DB.getInstance();
		int articleIndex = db.dbBoard.insertArticle(article);		
		 
        String nextPage = session.getAttribute("root")+"/board/articleView.do?boardName="+boardName+"&articleIndex="+articleIndex+"&currPage="+currPage;
        
		response.sendRedirect(nextPage);     
	}
}
