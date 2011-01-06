package servletBoard;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.Article;

import dbaccess.DB;

/**
 * Servlet implementation class ArticleModify
 */
@WebServlet("/ArticleModify")
public class ArticleModify extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleModify() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session = request.getSession();
		String userId = (String)session.getAttribute("userId");
		String currPage = request.getParameter("currPage");
		String boardName = request.getParameter("boardName");	
		
		DB db = DB.getInstance();
		int articleIndex = Integer.parseInt(request.getParameter("articleIndex"));
		Article article= db.dbBoard.getArticleByIndex(articleIndex);		
		
		//글쓴이와 id가 일치하지 않는 경우
		if(article.getUserId().compareTo(userId)!=0)  
		{
			response.sendRedirect("articleList.do?boardName="+boardName+"&currPage="+currPage);
			return;
		}	
		
		request.setAttribute("articleInfo",article);
		String nextPage = "/board/articleModify.jsp?boardName="+boardName+"&articleIndex="+articleIndex+"&currPage="+currPage;
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
}
