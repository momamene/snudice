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

import beans.ArticleInfo;

import dbaccess.DB;

/**
 * Servlet implementation class ArticleView
 */
@WebServlet("/ArticleView")
public class ArticleView extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleView() {
        super();
        // TODO Auto-generated constructor stub
    }    
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	doGet(request,response);
    }
    
	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		int articleIndex =  Integer.parseInt( request.getParameter("articleIndex"));
		HttpSession session = request.getSession();
		String userId = (String)session.getAttribute("userId");
		
		DB db = DB.getInstance();
		//자기가 쓴 글이 아닐 경우 조회수 증가		
		ArticleInfo article= db.dbBoard.getArticleByIndex(articleIndex);
		if(article.getUserId().compareTo(userId)!=0)
		{
			request.setAttribute("myArticle", false);
			db.dbBoard.updateArticleReadCount(articleIndex);
		}
		else
			request.setAttribute("myArticle", true);
		
		article.setTitle(Util.toHtml(article.getTitle()));
		article.setText(Util.toHtml(article.getText()));
		
		request.setAttribute("articleInfo",article);
		
		String nextPage = "board/articleView.jsp";	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
		
	}

}
