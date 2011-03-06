package ajax;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import dbaccess.DB;

/**
 * Servlet implementation class CreateBoard
 */
@WebServlet("/CreateBoard")
public class CreateBoard extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public CreateBoard() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String boardName = request.getParameter("boardName");
		String aliasName = request.getParameter("aliasName");
		
		DB db = DB.getInstance();
		boolean success = db.dbBoard.createBoard(boardName, aliasName);
		
		PrintWriter pw = response.getWriter();
		
		if(success)
			pw.print("OK");
		else
			pw.print("Fail");
	}
}