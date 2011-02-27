package ajax;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import dbaccess.DB;

import utility.GmailSend;

/**
 * Servlet implementation class IdFind
 */
@WebServlet("/IdFind")
public class IdFind extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public IdFind() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String email = request.getParameter("email");	
		ServletOutputStream os = response.getOutputStream();		
		
		DB db = DB.getInstance();
		String[] id = db.dbAccount.getIdWithEmail(email);
		if(id==null)
		{
			os.print("emailNotFound");
			return;
		}
		
		String subject = "snudice 계정 id 찾기 메일";				
		String msg = "이 메일계정으로 가입된 회원님의 id는 다음과 같습니다.";
		for(int i=0;i<id.length;i++)
			msg += "\n"+id[i];
		
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
		
		os.print("idFindOK");
	}
}
