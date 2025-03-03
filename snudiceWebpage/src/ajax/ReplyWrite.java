package ajax;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import constant.Const;

import dbaccess.DB;

/**
 * Servlet implementation class ReplyWrite
 */
@WebServlet("/ReplyWrite")
public class ReplyWrite extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ReplyWrite() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session = request.getSession();		
		String nickname = (String)session.getAttribute("nickname");		
		
		int articleIndex = Integer.parseInt(request.getParameter("articleIndex"));
		String replyText = request.getParameter("replyText");		
		
		//댓글 삽입
		if((Boolean)request.getAttribute("canComment")==true)
		{
			PrintWriter pw = response.getWriter();
			
			DB db = DB.getInstance();
			int replyCount = db.dbBoard.getReplyCount(articleIndex);
			if(replyCount < Const.replyLimit)
			{
				db.dbBoard.insertReply(articleIndex,nickname,replyText);
				pw.print("OK");
			}
			else
				pw.print("replyLimit");
		}
	}
}
