package servletBoard;

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
		if((Boolean)request.getAttribute("canRead")==false)
		{
			String root = (String)Util.getServletContextAttr(request, "root");
			response.sendRedirect(root);
			return;
		}
		
		int articleIndex =  Integer.parseInt( request.getParameter("articleIndex"));
		HttpSession session = request.getSession();
		String nickname = (String)session.getAttribute("nickname");
		String boardName = request.getParameter("boardName");
		int currPage = Integer.parseInt(request.getParameter("currPage"));	
		
		DB db = DB.getInstance();
		//글 정보를 가져옴
		Article article= db.dbBoard.getArticleByIndex(articleIndex);
		//자기가 쓴 글이 아닐 경우 조회수 증가		
		if(article.getNickname().compareTo(nickname)!=0)
		{
			request.setAttribute("myArticle", false);
			db.dbBoard.updateArticleReadCount(articleIndex);
		}
		else
			request.setAttribute("myArticle", true);		
		
		request.setAttribute("articleInfo",article);	
		
		//글쓴이의 권한정보를 가져옴
		String writerId = db.dbAccount.getUserIdWithNickname(article.getNickname());
		String writerRole = db.dbAccount.getUserRole(writerId);
		boolean isGM = ( writerRole.compareTo("admin")==0 || writerRole.compareTo("manager")==0 );
		request.setAttribute("isGM",isGM);
		
		//댓글들을 가져옴
		List<Reply> replyList = db.dbBoard.getReplyList(articleIndex);
		List<Boolean> replierIsGMList = new ArrayList<Boolean>();
		for(Reply reply : replyList)
		{
			String replyId = db.dbAccount.getUserIdWithNickname(reply.getNickname());
			String replierRole = db.dbAccount.getUserRole(replyId);
			boolean replierIsGM = ( replierRole.compareTo("admin")==0 || replierRole.compareTo("manager")==0 );
			replierIsGMList.add(replierIsGM);	
			reply.setNickname(Util.encodeHtml(reply.getNickname()));
			reply.setReplyText(Util.encodeHtml(reply.getReplyText()));			
		}
		request.setAttribute("replyList", replyList);
		request.setAttribute("replierIsGMList", replierIsGMList);
		request.setAttribute("replyCount", replyList.size());
		
		String nextPage = "/board/articleView.jsp?boardName="+boardName+"&currPage="+currPage;	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
}
