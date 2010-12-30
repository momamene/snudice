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
		HttpSession session = request.getSession();
		session.setMaxInactiveInterval(3600);
		session.setAttribute("root",Const.root);		
				
		final int articlePerPage = Const.articlePerPage;//페이지당 보여주는 게시물 수		
		
		String boardName = "free";		
		int currPage = 0;
		
		DB db = DB.getInstance();
		int totalArticleCount = db.dbBoard.getArticleCount(boardName);	
		int totalPageCount = (int)Math.ceil((double)totalArticleCount / (double)articlePerPage);		
					
		//리플 수를 저장
		List<Integer> replyCountList = new ArrayList<Integer>();
		
		//글 목록을 가져온다.
		List<Article> articleList = db.dbBoard.getArticleList(boardName,currPage, articlePerPage);		
		for(Article article : articleList)		
		{
			article.setTitle(Util.toHtml(article.getTitle()));
			int replyCount = db.dbBoard.getReplyCount(article.getArticleIndex());
			replyCountList.add(replyCount);			
		}
		
		request.setAttribute("replyCountList", replyCountList);
		
		List<Integer> pageList= new ArrayList<Integer>();		
		
		if(articleList.size()>0)
		{
			//page 번호들로 이루어진 리스트를 만든다.
			int pageListStart = (currPage/Const.pageNumberPerPage)*Const.pageNumberPerPage;
			for(int i = pageListStart; i<pageListStart+Const.pageNumberPerPage; i++)
			{			
				pageList.add(new Integer(i));
				if(i==totalPageCount-1)
					break;
			}
		}		
		
		request.setAttribute("pageList",pageList);
		request.setAttribute("articleList",articleList);
		request.setAttribute("currPage",currPage);
		request.setAttribute("endPage",totalPageCount-1);
		
		String nextPage = "login.jsp";
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
}
