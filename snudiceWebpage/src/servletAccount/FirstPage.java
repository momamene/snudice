package servletAccount;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.Util;
import beans.Article;

import constant.Const;
import dbaccess.DB;

/**
 * Servlet implementation class FirstPage
 */
@WebServlet("/FirstPage")
public class FirstPage extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public FirstPage() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		DB db = DB.getInstance();		
		//공지 글 목록을 가져온다.		
		List<Integer> replyCountList = new ArrayList<Integer>(); //리플 수 저장용
		
		List<Article> articleList = db.dbBoard.getArticleList("notice",0, Const.artilcePerPageMain);		
		for(Article article : articleList)		
		{
			article.setTitle(Util.toHtml(article.getTitle()));
			int replyCount = db.dbBoard.getReplyCount(article.getArticleIndex());
			replyCountList.add(replyCount);			
		}
		
		request.setAttribute("articleList",articleList);
		request.setAttribute("replyCountList", replyCountList);
		request.setAttribute("boardName", "notice");
		
		//게시판 목록을 가져온다.
		request.setAttribute("boardList", db.dbBoard.getBoardList());
		
		String nextPage = "login.jsp";
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
}
