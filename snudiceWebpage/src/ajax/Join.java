package ajax;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import utility.Encrypt;

import constant.Const;

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
		String joinId = request.getParameter("joinId");
		String joinPw = request.getParameter("joinPw");			
		String joinEmail = request.getParameter("joinEmail");		
		
		ServletOutputStream os = response.getOutputStream();		
		
		//parameter validation		
		if(joinId.indexOf(' ')>=0)
			os.print("idContainSpace");	
		else if(joinId.length()>Const.userIdMaxLen)
			os.print("idTooLong");
		else if(joinPw.indexOf(' ')>=0)				
			os.print("pwContainSpace");	
		else if(joinPw.length()>Const.passwordMaxLen)
			os.print("pwTooLong");
		else if(joinEmail.indexOf(' ')>=0)
			os.print("emailContainSpace");
		else if(joinEmail.length()>Const.emailMaxLen)
			os.print("emailTooLong");					
		else
		{
			DB db = DB.getInstance();
			boolean isExistingUser = db.dbAccount.isExistingUser(joinId);
			if(isExistingUser)
				os.print("existingUser");			
			else
			{				
				//계정 추가 - md5를 한번 더 적용해서 저장함
				db.dbAccount.insertNewUser(joinId,Encrypt.md5(joinPw),joinEmail,"member");	
				os.print("joinOK");
			}			
		}		
	}
}
