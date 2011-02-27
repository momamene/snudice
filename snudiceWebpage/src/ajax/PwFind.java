package ajax;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import utility.Encrypt;
import utility.GmailSend;
import utility.Util;
import dbaccess.DB;

/**
 * Servlet implementation class PwFind
 */
@WebServlet("/PwFind")
public class PwFind extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public PwFind() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String id = request.getParameter("id");	
		ServletOutputStream os = response.getOutputStream();		
		
		DB db = DB.getInstance();
		String email = db.dbAccount.getEmailWithId(id);
		if(email==null)
		{
			os.print("idNotFound");
			return;
		}		
		
		String subject = "snudice 계정 pw 찾기 메일";	
		String newPw = Util.getNewPw();		
		String msg = "회원님의 새로운 pw는 "+newPw+" 입니다.";
		msg += "\n반드시 새로운 비밀번호로 변경하시기 바랍니다.";
		
		try 
		{
			GmailSend gs = GmailSend.getInstance();	
			gs.sendSSLMessage(new String[]{email}, subject, msg, "snudice");
		}
		catch(Exception e)
		{
			os.print("emailSendingFail");
			return;
		}		
		
		db.dbAccount.setPassword(id, Encrypt.md5(Encrypt.md5(newPw)));
		os.print("pwFindOK");		
	}
}
