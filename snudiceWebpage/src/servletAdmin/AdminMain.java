package servletAdmin;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import constant.Const;
import dbaccess.DB;

/**
 * Servlet implementation class AdminMain
 */
@WebServlet("/AdminMain")
public class AdminMain extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AdminMain() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {		
		//게시판 목록을 가져온다.
		DB db = DB.getInstance();
		request.setAttribute("boardList", db.dbBoard.getBoardList());
			
		String nextPage = "admin/adminMain.jsp";	
		RequestDispatcher view = request.getRequestDispatcher(nextPage);
		view.forward(request, response);	
	}
}
