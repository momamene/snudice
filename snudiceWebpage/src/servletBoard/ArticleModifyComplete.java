package servletBoard;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import constant.Const;

import utility.Util;

import beans.Article;
import dbaccess.DB;

/**
 * Servlet implementation class articleModifyComplete
 */
@WebServlet("/articleModifyComplete")
public class ArticleModifyComplete extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
  
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String root = (String)Util.getServletContextAttr(request, "root");
		
		if((Boolean)request.getAttribute("canWrite")==false)
		{
			response.sendRedirect(root);
			return;
		}
		
		HttpSession session = request.getSession(); 		
		
		String nickname = (String) session.getAttribute("nickname");
		String boardName = request.getParameter("boardName");
		String currPage = request.getParameter("currPage");		
		String title = request.getParameter("title");
		String content = request.getParameter("content");		
		int articleIndex=Integer.parseInt( request.getParameter("articleIndex"));
				
		//길면 자른다.
		if(title.length()>Const.articleTitleMaxLen)
			title = title.substring(0,Const.articleTitleMaxLen);
		if(content.length()>Const.articleTextMaxLen)
			content = content.substring(0,Const.articleTextMaxLen);	
		
		//제목을 안적은 경우
		if(title.compareTo("")==0)		
			title = Util.currDateTime() + " 에 수정한 글입니다.";		
		
		Article article = new Article(boardName,nickname,title, content);		
		article.setArticleIndex(articleIndex);
		article.setRawStr(true);
		
		//글을 수정한다.
		DB db = DB.getInstance();
		db.dbBoard.updateArticle(article);		
		
        String nextPage = root+"/board/articleView.do?boardName="+boardName+"&currPage="+currPage+"&articleIndex="+articleIndex;        
		response.sendRedirect(nextPage);     
	}
}
