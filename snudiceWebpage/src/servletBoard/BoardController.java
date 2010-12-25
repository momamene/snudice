package servletBoard;

import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import beans.ArticleInfo;

import dbaccess.DB;

/**
 * Servlet implementation class boradList
 */
@WebServlet("/boardList")
public class BoardController extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public BoardController() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doProcess(request,response);
	}	

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {		
		doProcess(request,response);		
	}
	
	private void doProcess(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {		
		System.out.println("controller");
		//어떤 action을 콜했는지 추출
		String boardName = request.getParameter("boardName");
		String action = request.getParameter("action");
		
		if(action.equals("list")) //list 를 보여달라는 명령이였을 시 
		{	
			System.out.println("list");
			DB db = DB.getInstance();
			int totalArticleCount = db.dbBoard.getArticleCount(boardName);//게시물 수
			int postingPerPage = 10;//페이지당 보여주는 게시물 수
			int nowPage = Integer.parseInt(request.getParameter("page"));//현재 페이지 번호
			int startPosting = nowPage* postingPerPage;//페이지에 보여지는 첫 게시물 번호
			int endPosting = startPosting +postingPerPage -1 ;//페이지에 보여지는 마지막 게시물 번호
			if(endPosting>totalArticleCount)//게시물 수 보다 endPosting이 커질 경우 값 조정
				endPosting = totalArticleCount;
			int totalPage = totalArticleCount / postingPerPage;
			if ((totalArticleCount % postingPerPage)!=0)
				totalPage ++;
			List<ArticleInfo> listValues = db.dbBoard.getArticleList(boardName,startPosting, endPosting);
			
			/*
			//이렇게 해도 됨
			for(int i=0;i<listValues.size();i++)
				listValues.get(i);
			*/
			/*
			Iterator<ArticleInfo> iterator = listValues.listIterator();
			
			
			while(iterator.hasNext()) //유저아이디를 출력해줌
			{
				ArticleInfo element = (ArticleInfo) iterator.next();
				System.out.println("user id is " + element.getUserId() );
			}
			*/
			request.setAttribute("listValues",listValues);
			request.setAttribute("nowPage",nowPage);
			request.setAttribute("totalPage",totalPage);			
			
			//view를 실행함
			ServletContext sc = getServletContext();    
	        RequestDispatcher rd = sc.getRequestDispatcher("/board/boardList.jsp");
	        rd.forward(request, response);
		}
		
	/*	else if(action.equals("write"))
		{
			
			ArticleInfo article = new ArticleInfo(request.getParameter("boardName"),
					request.getParameter("userId"),
					request.getParameter("title"), request.getParameter("content"),
					request.getParameter("dateTime"));
			
			DB db = DB.getInstance();
			db.dbBoard.insertArticle(article);
			//view를 실행함
			ServletContext sc = getServletContext();    
	        RequestDispatcher rd = sc.getRequestDispatcher("/board/writeSuccess.jsp");
	        rd.forward(request, response);
	        
		
			//TODO: form에서 아이디하고 쓴날짜도 보내줘야 됨.
		}*/
		
	}	
}