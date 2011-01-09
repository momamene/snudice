package servletBoard;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
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
		if((Boolean)request.getAttribute("canWrite")==false)
		{
			String root = (String)Util.getServletContextAttr(request, "root");
			response.sendRedirect(root);
			return;
		}
		
		HttpSession session = request.getSession();
		String userId = (String)session.getAttribute("userId");
		String currPage = request.getParameter("currPage");
		String boardName = request.getParameter("boardName");	
		
		DB db = DB.getInstance();
		int articleIndex = Integer.parseInt(request.getParameter("articleIndex"));
		Article article= db.dbBoard.getArticleByIndex(articleIndex);
		article.setRawStr(true);
		
		//글쓴이와 id가 일치하지 않는 경우 ( admin 도 남의 글을 수정할 수는 없음 )
		if(article.getUserId().compareTo(userId)!=0)  
		{
			response.sendRedirect("articleList.do?boardName="+boardName+"&currPage="+currPage);
			return;
		}		
		
		request.setAttribute("article",article);
		String nextPage = "/board/articleModify.jsp?boardName="+boardName+"&articleIndex="+articleIndex+"&currPage="+currPage;
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
}
