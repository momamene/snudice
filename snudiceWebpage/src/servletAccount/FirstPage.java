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
		
		//게시판 목록을 가져온다.
		request.setAttribute("boardList", db.dbBoard.getBoardList());
		
		//공지,이벤트,개발자노트,업데이트 게시판의 최신글 목록을 가져옴
		setArticleList(request,"notice","noticeBoardName","noticeList");
		setArticleList(request,"event","eventBoardName","eventList");
		setArticleList(request,"devNote","devNoteBoardName","devNoteList");
		setArticleList(request,"update","updateBoardName","updateList");
				
		String nextPage = "login.jsp";
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
	
	//board 에서 글들을 가져와서 request 에 속성으로 설정한다.
	private void setArticleList(HttpServletRequest request,String boardName,String boardNameAttrbName,String articleListName) {
		DB db = DB.getInstance();
		
		//공지 글 목록을 가져온다.				
		List<Article> articleList = db.dbBoard.getArticleList(boardName,0, Const.artilcePerPageMain);		
		for(Article article : articleList)			
			article.setTitle(Util.toHtml(article.getTitle()));			
		
		request.setAttribute(articleListName,articleList);
		request.setAttribute(boardNameAttrbName, boardName);
	}
}
