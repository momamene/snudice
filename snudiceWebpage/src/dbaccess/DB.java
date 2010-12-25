package dbaccess;

import java.io.Reader;

import com.ibatis.common.resources.Resources;
import com.ibatis.sqlmap.client.SqlMapClient;
import com.ibatis.sqlmap.client.SqlMapClientBuilder;


//Singleton
public class DB {
	////////////////////////////////////////////////
	public DBAccount dbAccount;	
	public DBBoard dbBoard;	
	////////////////////////////////////////////////
	
	private String configXMLFile = "SqlMapConfig.xml"; //xml file명	
	private static DB instance = new DB();
	private SqlMapClient sqlMap;
	private Reader reader;
	
	private DB() {
		try
		{
			reader = Resources.getResourceAsReader(configXMLFile);			
			sqlMap = SqlMapClientBuilder.buildSqlMapClient(reader);
		}
		catch(Exception e)
		{			
			e.printStackTrace();
			System.out.println("\nError : in DB() (constructor)");
		}
		
		////////////////////////////////////////////////
		dbAccount = DBAccount.getInstance(sqlMap);
		dbBoard = DBBoard.getInstance(sqlMap);		
		////////////////////////////////////////////////
	}
	
	public static DB getInstance() {
		return instance;
	}

}
