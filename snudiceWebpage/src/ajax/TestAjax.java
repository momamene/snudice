package ajax;

import java.io.IOException;
import java.util.Enumeration;

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
		
		//모든 인자를 출력한다.
		Enumeration<String> e = request.getParameterNames();
		while(e.hasMoreElements())
		{
			String paramName = e.nextElement();
			System.out.println(paramName+"="+request.getParameter(paramName));
		}		
		
		//stream의 내용을 그대로 출력한다. (JSON string 확인 등에 사용)
		//이것을 사용할 경우 위의 모든 인자 출력 코드를 주석처리 해야 한다.
		/*
		BufferedReader r = request.getReader();
		char[] buf= new char[256];
		while(r.read(buf)>0)
			System.out.println(buf);
		*/		
	}
}
