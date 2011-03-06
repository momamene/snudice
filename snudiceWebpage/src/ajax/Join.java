package ajax;

import java.io.IOException;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import utility.Encrypt;
import utility.GmailSend;
import utility.Util;

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
		String joinNickname = request.getParameter("joinNickname");
		String joinComment = request.getParameter("joinComment");
		
		ServletOutputStream os = response.getOutputStream();		
		
		//parameter validation		
		if(joinId.indexOf(' ')>=0)
			os.print("idContainSpace");	
		else if(joinId.length()>Const.userIdMaxLen)
			os.print("idTooLong");
		else if(joinPw.indexOf(' ')>=0)				
			os.print("pwContainSpace");			
		else if(joinEmail.indexOf(' ')>=0)
			os.print("emailContainSpace");
		else if(joinEmail.length()>Const.emailMaxLen)
			os.print("emailTooLong");			
		else if(joinNickname.indexOf(' ')>=0)
			os.print("nicknameContainSpace");
		else if(Util.getByteCnt(joinNickname)>Const.nicknameMaxLen)
			os.print("nicknameTooLong");		
		else if(Util.getByteCnt(joinComment)>Const.commentMaxLen)
			os.print("commentTooLong");
		else
		{
			DB db = DB.getInstance();
			boolean isExistingUser = db.dbAccount.isExistingUser(joinId);
			boolean isExistingNickname = db.dbAccount.isExistingNickname(joinNickname);
			if(isExistingUser)
				os.print("existingUser");			
			else if(isExistingNickname)
				os.print("existingNickname");
			else
			{				
				//인증용 email 전송
				String activationCode = Util.getActivationCode();
				
				ServletContext sc = request.getServletContext();
				
				String subject = "snudice 계정 활성화 인증 메일";				
				String msg = joinId+" 님, snudice 가입신청에 감사드립니다.\n\n";				
				msg += "다음 링크를 클릭하여 계정을 활성화 해주세요\nhttp://";
				msg += sc.getAttribute("domain");
				msg += sc.getAttribute("root")+"/";
				msg += "activate.do?userId="+joinId;
				msg += "&code="+activationCode;
				
				try 
				{
					GmailSend gs = GmailSend.getInstance();	
					gs.sendSSLMessage(new String[]{joinEmail}, subject, msg, "snudice");
				}
				catch(Exception e)
				{
					os.print("emailSendingFail");
					return;
				}
				
				//계정 추가 - md5를 한번 더 적용해서 저장함				
				db.dbAccount.insertNotActivatedUser(joinId, Encrypt.md5(joinPw), joinEmail, joinNickname, joinComment, activationCode, "member");				
				os.print("joinOK");				
			}			
		}		
	}
}
