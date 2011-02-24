package servletAccount;

import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
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
		//공지,업데이트 게시판의 최신글 목록을 가져옴
		setArticleList(request,"notice","noticeList");		
		setArticleList(request,"update","updateList");		
				
		String nextPage = "login.jsp";
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);		
	}
	
	//board 에서 글들을 가져와서 request 에 속성으로 설정한다.
	private void setArticleList(HttpServletRequest request,String boardName,String articleListName) {
		DB db = DB.getInstance();				
		List<Article> articleList = db.dbBoard.getArticleList(boardName,0, Const.artilcePerPageMain);		
		request.setAttribute(articleListName,articleList);
	}
}
