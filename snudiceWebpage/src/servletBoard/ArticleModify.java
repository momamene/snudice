package servletBoard;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.catalina.Session;

import beans.ArticleInfo;

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
		
		//아이디 검사 후
		HttpSession session = request.getSession();
		DB db = DB.getInstance();
		int articleIndex = Integer.parseInt(request.getParameter("articleIndex"));
		ArticleInfo article= db.dbBoard.getArticleByIndex(articleIndex);
		if(session.getAttribute("userId")!=article.getUserId())
		{
			// 아이디 불일치 시 ...
		}
		
		request.setAttribute("articleInfo",article);
		String nextPage = "board/articleModify.jsp";	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
		
		//ok -> modify.jsp로 이동
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */


}
