package servletBoard;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.Util;

/**
 * Servlet implementation class ArticleWriteForm
 */
@WebServlet("/ArticleWriteForm")
public class ArticleWriteForm extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ArticleWriteForm() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		if((Boolean)request.getAttribute("canWrite")==false)
		{
			String root = (String)Util.getServletContextAttr(request, "root");
			response.sendRedirect(root);
			return;
		}
		
		String boardName = request.getParameter("boardName");
		String currPage = request.getParameter("currPage");
		
		String nextPage = "/board/articleWrite.jsp?boardName="+boardName+"&currPage="+currPage;	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);
	}
}
