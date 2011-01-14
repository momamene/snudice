package dbaccess;

import java.util.List;

import beans.User;
import beans.UserRole;

import com.ibatis.sqlmap.client.SqlMapClient;

//singleton
public class DBAccount {
	private volatile static DBAccount instance = null;
	private SqlMapClient sqlMap = null;
	
	private DBAccount(SqlMapClient sqlMap) {		
		this.sqlMap = sqlMap;
	}
	
	//DCL(Double-Checking Locking) 을 사용하여 동기화
	public static DBAccount getInstance(SqlMapClient sqlMap) {
		if(instance==null)
		{
			synchronized(DBAccount.class)
			{
				if(instance==null)
				{
					instance = new DBAccount(sqlMap);
				}
			}
		}
		return instance;
	}	
	
	//user id, password를 검사한다.
	public boolean isValidUser(String userId,String password) {
		User user = new User(userId,password,null);
		
		Integer userCount = null;
		try {			
			userCount = (Integer)sqlMap.queryForObject("countUserWithPassword",user);	
		}
		catch(Exception e)
		{			
			e.printStackTrace();
		}		
		
		if(userCount==0) //count가 0이면
			return false;
		return true;
	}	
	
	//user가 존재하는지를 검사한다.
	public boolean isExistingUser(String userId) {		
		Integer userCount = null;
		try {			
			userCount = (Integer)sqlMap.queryForObject("countUser",userId);	
		}
		catch(Exception e)
		{			
			e.printStackTrace();
		}		
		
		if(userCount==0) //count가 0이면
			return false;
		return true;
	}
	
	//email이 존재하는지를 검사한다.
	public boolean isExistingEmail(String email) {		
		Integer emailCount = null;
		try {			
			emailCount = (Integer)sqlMap.queryForObject("countEmail",email);	
		}
		catch(Exception e)
		{			
			e.printStackTrace();
		}		
		
		if(emailCount==0) //count가 0이면
			return false;
		return true;
	}

	//새로운 user를 추가한다.
	public void insertNewUser(String userId, String password,String email,String role) {	
		User newUser = new User(userId,password,email);
		UserRole newUserRole = new UserRole(userId,role);
		try {
			sqlMap.insert("insertUser",newUser);
			sqlMap.insert("insertUserRole",newUserRole);
			sqlMap.insert("insertUserScore",userId);

		} catch (Exception e) {			
			e.printStackTrace();
		}
	}

	//user의 role 정보를 얻는다.
	@SuppressWarnings("unchecked")
	public String getUserRole(String remoteUser) {
		List<String> result = null;
		try {			
			result = (List<String>)sqlMap.queryForList("getUserRole",remoteUser);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		return result.get(0);
	}		
}
