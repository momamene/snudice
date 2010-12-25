package servletBoard;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

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

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		
		//
		int articleIndex =  Integer.parseInt( request.getParameter("articleIndex"));
		DB db = DB.getInstance();
		ArticleInfo article= db.dbBoard.getArticleByIndex(articleIndex);
		db.dbBoard.updateArticleReadCount(articleIndex);
		System.out.println(article.getText());
		article.setText(article.getText().replace("\n", "<br>"));
		request.setAttribute("articleInfo",article);
		String nextPage = "board/articleView.jsp";	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
		
	}

}
