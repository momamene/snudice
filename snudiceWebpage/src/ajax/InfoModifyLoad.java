package ajax;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import beans.User;

import com.google.gson.Gson;

import dbaccess.DB;

/**
 * Servlet implementation class InfoModifyLoad
 */
@WebServlet("/InfoModifyLoad")
public class InfoModifyLoad extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public InfoModifyLoad() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String userId = request.getParameter("userId");			
		
		response.setContentType("text/plain; charset=UTF-8");
		response.setCharacterEncoding("UTF-8");
		PrintWriter pw = response.getWriter();
		
		DB db = DB.getInstance();
		User user = null;
		try
		{
			user = db.dbAccount.getUser(userId);
		}
		catch(RuntimeException re)
		{
			pw.print("error");
			return;
		}

		Gson gson = new Gson();
		HashMap<String,String> userInfo = new HashMap<String,String>();
		userInfo.put("email", user.getEmail());
		userInfo.put("comment", user.getComment());
		String json = gson.toJson(userInfo);	
			
		pw.print(json);		
	}
}