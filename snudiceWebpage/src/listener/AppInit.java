package listener;

import java.util.List;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;
import javax.servlet.http.HttpServletRequest;

import beans.Article;
import constant.Const;
import dbaccess.DB;

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
    	//DD에 적힌 초기화 파라매터를 읽어 속성으로 설정한다. 
        ServletContext sc = event.getServletContext();
        String domain = sc.getInitParameter("domain");
        String root = sc.getInitParameter("root");
        String footerMsg = sc.getInitParameter("footerMsg");        
        
        sc.setAttribute("domain", domain);    
        sc.setAttribute("root", root);        
        sc.setAttribute("footerMsg", footerMsg);
        
        //menu에 사용할 것들을 속성으로 설정한다.
		DB db = DB.getInstance();
		String freeBoardName = "free";
		String freeBoardAliasName = db.dbBoard.getBoardAliasName(freeBoardName);
		sc.setAttribute("freeBoardName",freeBoardName);
		sc.setAttribute("freeBoardAliasName", freeBoardAliasName);
    }


	/**
     * @see ServletContextListener#contextDestroyed(ServletContextEvent)
     */
    public void contextDestroyed(ServletContextEvent event) {
        // TODO Auto-generated method stub
    }
	
}
