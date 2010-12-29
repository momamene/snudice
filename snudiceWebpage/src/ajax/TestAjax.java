package ajax;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class TestAjax
 */
@WebServlet("/TestAjax")
public class TestAjax extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public TestAjax() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("AJAX 요청! GET");	
		doPost(request,response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("AJAX 요청! POST(GET이 떴다면 GET에서 포워딩 된것이므로 GET인 거임)");	

		request.setCharacterEncoding("UTF-8");		
		
		BufferedReader r = request.getReader();
		char[] buf= new char[256];
		while(r.read(buf)>0)
			System.out.println(buf);
		
		System.out.println(request.getParameter("arg0"));
		System.out.println(request.getParameter("arg1"));
	}
}
