package servletBoard;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import constant.Const;


import beans.ArticleInfo;
import dbaccess.DB;

/**
 * Servlet implementation class BoardList
 */
@WebServlet("/ArticleList")
public class ArticleList extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleList() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		final int articlePerPage = Const.articlePerPage;//페이지당 보여주는 게시물 수		
		HttpSession session = request.getSession();
		String boardName=(String) session.getAttribute("boardName");
		
		//boardName 처리 
		if(request.getParameter("boardName")!=null)
		{
			boardName = request.getParameter("boardName");			
		}
		session.setAttribute("boardName", boardName);


		//현재 page 값 구하기 
		int currPage;
		if(request.getParameter("currPage")!=null)
			currPage = Integer.parseInt(request.getParameter("currPage")); //현재 페이지 번호
		else if(session.getAttribute("currPage")!=null)
			currPage = (Integer) session.getAttribute("currPage");
		else
			currPage = 0;
		
		
		DB db = DB.getInstance();
		int totalArticleCount = db.dbBoard.getArticleCount(boardName);//총 게시물 수		
		int endPage = totalArticleCount / articlePerPage;
		if ((totalArticleCount % articlePerPage)==0)
			endPage --;
		System.out.println("end page is " + endPage);
		
		//전 페이지 범위로 넘어가라는 명령을 받았을 때
		if(request.getParameter("goPrev")!=null&&currPage>=10)
		{
			currPage =  currPage /10;
			currPage = currPage * 10 - 10;
		}
		if(request.getParameter("goNext")!=null && (currPage/10)< (endPage/10))
		{
			System.out.println("gonext!");
			currPage = currPage /10;
			currPage =currPage * 10 + 10;
		}
		
		int startArticleIndex = currPage*articlePerPage;//페이지에 보여지는 첫 게시물 번호
		
		session.setAttribute("currPage", currPage);
		
	
		List<ArticleInfo> articleList = db.dbBoard.getArticleList(boardName,startArticleIndex, 10);
		
		/*for(ArticleInfo article : articleList)
		{
			System.out.println(article.toString());
		} */
		List<Integer> pageList= new ArrayList<Integer>();
		
		for(int i = (currPage/10)* 10; i<=endPage; i++)
		{
			Integer temp= new Integer(i);
			pageList.add(temp);
			if(i==9)
				break;
		}
		request.setAttribute("pageList",pageList);
		request.setAttribute("articleList",articleList);
		request.setAttribute("currPage",currPage);
		request.setAttribute("endPage",endPage);		
		
		String nextPage = "board/articleList.jsp";
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
	}
}