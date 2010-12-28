package servletBoard;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.ArticleInfo;

import dbaccess.DB;

/**
 * Servlet implementation class ArticleDelete
 */
@WebServlet("/ArticleDelete")
public class ArticleDelete extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleDelete() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session = request.getSession();
		String userId = (String)session.getAttribute("userId");	
		
		//로그인 된 상태가 아닌 경우
		if(userId==null)
		{			
			response.sendRedirect("first.do");
			return;
		}		
		
		String boardName = request.getParameter("boardName");
		String currPage = request.getParameter("currPage");
		int articleIndex = Integer.parseInt(request.getParameter("articleIndex"));
		
		DB db = DB.getInstance();
		ArticleInfo article= db.dbBoard.getArticleByIndex(articleIndex);
		if(article.getUserId().compareTo(userId)!=0) //아이디가 글쓴이와 일치하면
		{
			//글을 지운다.		
			db.dbBoard.deleteArticle(articleIndex);
		}		
		
		String nextPage = "articleList.do?boardName="+boardName+"&currPage="+currPage;		
			
		response.sendRedirect(nextPage);
	}
}
