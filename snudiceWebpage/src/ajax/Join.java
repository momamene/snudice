package ajax;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import dbaccess.DB;

/**
 * Servlet implementation class Join
 */
@WebServlet("/Join")
public class Join extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Join() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {		
		request.setCharacterEncoding("utf-8");
		
		String joinId = request.getParameter("joinId");
		String joinPw = request.getParameter("joinPw");			
		String joinEmail = request.getParameter("joinEmail");
		
		ServletOutputStream os = response.getOutputStream();		
		
		//parameter validation		
		if(joinId.indexOf(' ')>=0)
			os.print("idContainSpace");		
		else if(joinPw.indexOf(' ')>=0)				
			os.print("pwContainSpace");
		else if(joinEmail.indexOf(' ')>=0)
			os.print("emailContainSpace");
		else
		{
			DB db = DB.getInstance();
			boolean isExistingUser = db.dbAccount.isExistingUser(joinId);
			if(isExistingUser)
				os.print("existingUser");			
			else
			{				
				//계정 추가
				db.dbAccount.insertNewUser(joinId,joinPw,joinEmail,"member");	
				os.print("joinOK");
			}			
		}		
	}
}
