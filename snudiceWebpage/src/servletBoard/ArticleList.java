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

import utility.Util;
import constant.Const;


import beans.Article;
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
		if((Boolean)request.getAttribute("canList")==false)
		{
			String root = (String)Util.getServletContextAttr(request, "root");
			response.sendRedirect(root);
			return;
		}
		
		final int articlePerPage = Const.articlePerPage;//페이지당 보여주는 게시물 수		
		
		String boardName = request.getParameter("boardName");		
		int currPage = Integer.parseInt(request.getParameter("currPage"));		
		
		DB db = DB.getInstance();
		int totalArticleCount = db.dbBoard.getArticleCount(boardName);	
		int totalPageCount = (int)Math.ceil((double)totalArticleCount / (double)articlePerPage);		
		
		//페이지 범위 넘어가는 처리
		if(request.getParameter("goPrev")!=null)
		{
			currPage -=  Const.pageNumberPerPage;
			if(currPage<0)
				currPage = 0;			
			
			response.sendRedirect("articleList.do?boardName="+boardName+"&currPage="+currPage);
			return;
		}
		if(request.getParameter("goNext")!=null)
		{
			currPage +=  Const.pageNumberPerPage;
			if(currPage>totalPageCount-1)
				currPage = totalPageCount-1;
			
			response.sendRedirect("articleList.do?boardName="+boardName+"&currPage="+currPage);
			return;
		}			
	
		//리플 수를 저장
		List<Integer> replyCountList = new ArrayList<Integer>();
		
		//관리자(admin,member)여부를 저장
		List<Boolean> isGMList = new ArrayList<Boolean>();
		
		//글 목록을 가져온다.		
		List<Article> articleList = db.dbBoard.getArticleList(boardName,currPage, articlePerPage);		
		for(Article article : articleList)						
			Util.articleInfoSet(db, replyCountList, isGMList, article);			
		
		request.setAttribute("replyCountList", replyCountList);
		request.setAttribute("isGMList", isGMList);
		
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
		
		String nextPage = "/board/articleList.jsp";
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);        
	}
}