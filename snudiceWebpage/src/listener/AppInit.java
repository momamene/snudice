package listener;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

/**
 * Application Lifecycle Listener implementation class AppInit
 *
 */
@WebListener
public class AppInit implements ServletContextListener {

    /**
     * Default constructor. 
     */
    public AppInit() {
        // TODO Auto-generated constructor stub
    }

	/**
     * @see ServletContextListener#contextInitialized(ServletContextEvent)
     */
    public void contextInitialized(ServletContextEvent event) {
    	//root 경로를 DD에 적힌 초기화 파라매터를 읽어 속성으로 설정한다. 
        ServletContext sc = event.getServletContext();
        String root = sc.getInitParameter("root");
        sc.setAttribute("root", root);
        
        //footer에 들어갈 메세지 설정
        String footerMsg = sc.getInitParameter("footerMsg");
        sc.setAttribute("footerMsg", footerMsg);       
    }

	/**
     * @see ServletContextListener#contextDestroyed(ServletContextEvent)
     */
    public void contextDestroyed(ServletContextEvent event) {
        // TODO Auto-generated method stub
    }
	
}
