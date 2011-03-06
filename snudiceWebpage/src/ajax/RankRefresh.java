package ajax;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import dbaccess.DB;

/**
 * Servlet implementation class RankRefresh
 */
@WebServlet("/RankRefresh")
public class RankRefresh extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public RankRefresh() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		//rank를 재계산한다.
		DB db = DB.getInstance();
		ArrayList<String> l = db.dbGame.evalGradeMaxRank();
		for(int i=0;i<l.size();i++)	
			db.dbGame.setGradeMaxRank(l.get(i), i+1);
		
		PrintWriter pw = response.getWriter();
		pw.print("OK");
	}
}
