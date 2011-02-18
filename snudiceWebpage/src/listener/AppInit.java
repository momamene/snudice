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
        String domain = sc.getInitParameter("domain");
        String root = sc.getInitParameter("root");
        String footerMsg = sc.getInitParameter("footerMsg");        
        
        sc.setAttribute("domain", domain);    
        sc.setAttribute("root", root);        
        sc.setAttribute("footerMsg", footerMsg);       
    }

	/**
     * @see ServletContextListener#contextDestroyed(ServletContextEvent)
     */
    public void contextDestroyed(ServletContextEvent event) {
        // TODO Auto-generated method stub
    }
	
}
