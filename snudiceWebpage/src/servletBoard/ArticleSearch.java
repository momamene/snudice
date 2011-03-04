package servletBoard;

import java.io.IOException;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import utility.Util;

import beans.Article;
import constant.Const;
import dbaccess.DB;

/**
 * Servlet implementation class ArticleSearch
 */
@WebServlet("/ArticleSearch")
public class ArticleSearch extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleSearch() {
        super();
        // TODO Auto-generated constructor stub
    }
    
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
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
		String titleKeyword = request.getParameter("titleKeyword");		
		
		DB db = DB.getInstance();		
		int totalArticleCount = db.dbBoard.getArticleCount(boardName,titleKeyword);
		int totalPageCount = (int)Math.ceil((double)totalArticleCount / (double)articlePerPage);		
	
		//리플 수를 저장
		List<Integer> replyCountList = new ArrayList<Integer>();
		
		//글 목록을 가져온다.
		List<Article> articleList = db.dbBoard.getArticleList(boardName,currPage,articlePerPage,titleKeyword);
		for(Article article : articleList)		
		{			
			//날짜 간략화
			String simpleDateTime = Util.getSimpleDateTime(article.getDateTime());
			article.setDateTime(simpleDateTime); 
			
			//제목 간략화(길면 자른다)
			article.setRawStr(true);
			String title = article.getTitle();								
			if(title.length()>Const.articleTitleInListMaxLen)
				article.setTitle((title.substring(0,Const.articleTitleInListMaxLen)+"...").getBytes());
			article.setRawStr(false);
			
			//리플수 저장
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
		
		//페이지 범위 넘어가는 처리
		if(request.getParameter("goPrev")!=null)
		{
			currPage -=  Const.pageNumberPerPage;
			if(currPage<0)
				currPage = 0;			
			
			titleKeyword = URLEncoder.encode(titleKeyword, "utf-8");
			response.sendRedirect("articleSearch.do?titleKeyword="+titleKeyword+"&boardName="+boardName+"&currPage="+currPage);
			return;
		}
		if(request.getParameter("goNext")!=null)
		{
			currPage +=  Const.pageNumberPerPage;
			if(currPage>totalPageCount-1)
				currPage = totalPageCount-1;
			
			titleKeyword = URLEncoder.encode(titleKeyword, "utf-8");
			response.sendRedirect("articleSearch.do?titleKeyword="+titleKeyword+"&boardName="+boardName+"&currPage="+currPage);
			return;
		}
		
		request.setAttribute("pageList",pageList);
		request.setAttribute("articleList",articleList);
		request.setAttribute("currPage",currPage);
		request.setAttribute("endPage",totalPageCount-1);	
		request.setAttribute("boardAliasName", db.dbBoard.getBoardAliasName(boardName));
		
		request.setAttribute("search","yes");
		request.setAttribute("titleKeyword", titleKeyword);
		
		String nextPage = "/board/articleList.jsp";
		
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);   
	}
}
