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
		String joinPwConfirm = request.getParameter("joinPwConfirm");	
		String joinEmail = request.getParameter("joinEmail");
		
		ServletOutputStream os = response.getOutputStream();
		os.print("OK");
		os.flush();
		
		
		/*		
		if(joinId.compareTo("")==0 || joinPw.compareTo("")==0 || joinEmail.compareTo("")==0)
			msg = "모든 항목을 채워주세요!";		
		else if(joinId.length()>16)
			msg = "id는 16자까지만 가능합니다.";
		else
		{
			DB db = DB.getInstance();
			boolean isExistingUser = db.dbAccount.isExistingUser(joinId);
			boolean isExistingEmail = db.dbAccount.isExistingEmail(joinEmail);
			if(isExistingUser)
				msg = "이미 존재하는 id 입니다.";
			else if(isExistingEmail)
				msg = "이미 존재하는 email 입니다.";
			else
			{
				nextPage = "joinSuccess.jsp";
				//계정 추가
				db.dbAccount.insertNewUser(joinId,joinPw,joinEmail);	
			}			
		}
		*/
	}
}
