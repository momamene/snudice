package servletBoard;

import java.io.IOException;
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
import beans.Reply;
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
		String boardName = request.getParameter("boardName");
		int currPage = Integer.parseInt(request.getParameter("currPage"));	
		
		DB db = DB.getInstance();
		//글 정보를 가져옴
		Article article= db.dbBoard.getArticleByIndex(articleIndex);
		//자기가 쓴 글이 아닐 경우 조회수 증가		
		if(article.getUserId().compareTo(userId)!=0)
		{
			request.setAttribute("myArticle", false);
			db.dbBoard.updateArticleReadCount(articleIndex);
		}
		else
			request.setAttribute("myArticle", true);		
		
		request.setAttribute("articleInfo",article);		
		
		//댓글들을 가져옴
		List<Reply> replyList = db.dbBoard.getReplyList(articleIndex);
		for(Reply reply : replyList)
		{
			reply.setUserId(Util.toHtml(reply.getUserId()));
			reply.setReplyText(Util.toHtml(reply.getReplyText()));
		}
		request.setAttribute("replyList", replyList);
		request.setAttribute("replyCount", replyList.size());
		
		String nextPage = "/board/articleView.jsp?boardName="+boardName+"&currPage="+currPage;	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
}
