package dbaccess;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import utility.Util;

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
		User user = new User(userId,password,null,null,null,null);
		
		Integer userCount = null;
		try {			
			userCount = (Integer)sqlMap.queryForObject("countUserWithPassword",user);	
		}
		catch(Exception e)
		{			
			e.printStackTrace();
		}		
		if(userCount==0) 
			return false;
		return true;
	}	
	
	//user가 존재하는지를 검사한다. (가입된 사람, 가입대기중인 사람 모두 체크)
	public boolean isExistingUser(String userId) {		
		Integer userCount = null;
		Integer userCount2 = null;
		try {			
			userCount = (Integer)sqlMap.queryForObject("countUser",userId);	
			userCount2 = (Integer)sqlMap.queryForObject("countUser2",userId);
		}
		catch(Exception e)
		{			
			e.printStackTrace();
		}		
		
		if(userCount==0 && userCount2==0) 
			return false;
		return true;
	}	
	
	//nickname이 존재하는지를 검사한다. (가입된 사람, 가입대기중인 사람 모두 체크)
	public boolean isExistingNickname(String nickname) {
		Integer nicknameCount = null;
		Integer nicknameCount2 = null;
		try {			
			nicknameCount = (Integer)sqlMap.queryForObject("countNickname",nickname);
			nicknameCount2 = (Integer)sqlMap.queryForObject("countNickname2",nickname);
		}
		catch(Exception e)
		{			
			e.printStackTrace();
		}		
		
		if(nicknameCount==0 && nicknameCount2==0) 
			return false;
		return true;
	}

	//새로운 user를 가입 대기상태로 만든다. 
	public void insertNotActivatedUser(String userId, String password,String email,String nickname,String comment,String activationCode,String role) {
		User newUser = new User(userId,password,email,nickname,comment,activationCode,role);
		newUser.setJoinDate(Util.currDateTime());
		try {
			sqlMap.insert("insertNotActivatedUser",newUser);			
		} catch (Exception e) {			
			e.printStackTrace();
		}
	}
	
	//가입 대기 상태인 user의 정보를 얻어온다.
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public User getNotActivatedUser(String userId,String activationCode) {
		List<User> result = null;
		try {	
			Map m = new HashMap();
			m.put("userId", userId);
			m.put("activationCode",activationCode);
			
			result = (List<User>)sqlMap.queryForList("getNotActivatedUser",m);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		if(result.size()==0)		
			throw new RuntimeException("getNotActivatedUser():잘못된 유저정보");
		
		return result.get(0);
	}
	
	//가입 대기상태인 유저를 삭제한다.
	public void deleteNotActivatedUser(String userId) {
		try {
			sqlMap.delete("deleteNotActivatedUser",userId);			
		} catch (Exception e) {			
			e.printStackTrace();
		}
	}
	
	//새로운 user를 추가한다.
	public void insertNewUser(User newUser) {	
		String userId = newUser.getUserId();
		String nickname = newUser.getNickname();
		UserRole newUserRole = new UserRole(userId,newUser.getRole());
		try {
			sqlMap.insert("insertUser",newUser);
			sqlMap.insert("insertUserRole",newUserRole);
			sqlMap.insert("insertUserScore",nickname);

		} catch (Exception e) {			
			e.printStackTrace();
		}
	}

	//user의 role 정보를 얻는다.
	@SuppressWarnings("unchecked")
	public String getUserRole(String userId) {
		List<String> result = null;
		try {			
			result = (List<String>)sqlMap.queryForList("getUserRole",userId);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		return result.get(0);
	}
	
	//userId 로부터 nickname을 얻는다.
	@SuppressWarnings("unchecked")
	public String getNickname(String userId) {
		List<String> result = null;
		try {			
			result = (List<String>)sqlMap.queryForList("getNickname",userId);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		return result.get(0);
	}
	
	//nickname 으로부터 userId를 얻는다.
	@SuppressWarnings("unchecked")
	public String getUserIdWithNickname(String nickname) {
		List<String> result = null;
		try {			
			result = (List<String>)sqlMap.queryForList("getUserIdWithNickname",nickname);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		return result.get(0);
	}

	//email 로 userId 를 얻는다.
	@SuppressWarnings("unchecked")
	public String[] getIdWithEmail(String email) {
		List<String> result = null;
		try {			
			result = (List<String>)sqlMap.queryForList("getIdWithEmail",email);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		if(result.size()==0)
			return null;
		
		String[] retVal = new String[result.size()];
		result.toArray(retVal);
		return retVal;
	}
	
	//userId로 email을 얻는다.
	@SuppressWarnings("unchecked")
	public String getEmailWithId(String userId) {
		List<String> result = null;
		try {			
			result = (List<String>)sqlMap.queryForList("getEmailWithId",userId);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		if(result.size()==0)
			return null;
		
		return result.get(0);
	}
	
	//새로운 password를 설정한다.
	//주의 : encodedPw 값이 그대로 DB로 들어가게 된다.
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void setPassword(String userId,String encodedPw) {
		Map m = new HashMap();
		m.put("userId",userId);
		m.put("password", encodedPw);
		try {			
			sqlMap.update("setPassword",m);
		} catch (Exception e) {			
			e.printStackTrace();
		}
	}
	
	//유저정보를 얻는다.
	@SuppressWarnings("unchecked")
	public User getUser(String userId) {
		List<User> result = null;
		try {			
			result = (List<User>)sqlMap.queryForList("getUser",userId);
		} catch (Exception e) {			
			e.printStackTrace();
		}
		
		if(result.size()==0)
			throw new RuntimeException(userId+" 가 존재하지 않습니다.");
		
		return result.get(0);
	}

	//유저 정보를 변경한다.
	public void setUser(User user) {
		try {			
			sqlMap.update("setUser",user);
		} catch (Exception e) {			
			e.printStackTrace();
		}		
	}
}
