package dbaccess;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import beans.Reply;

import com.ibatis.sqlmap.client.SqlMapClient;

public class DBGame {
	private volatile static DBGame instance = null;
	private SqlMapClient sqlMap = null;
	
	private DBGame(SqlMapClient sqlMap) {		
		this.sqlMap = sqlMap;
	}
	
	//DCL(Double-Checking Locking) 을 사용하여 동기화
	public static DBGame getInstance(SqlMapClient sqlMap) {
		if(instance==null)
		{
			synchronized(DBGame.class)
			{
				if(instance==null)
				{
					instance = new DBGame(sqlMap);
				}
			}
		}
		return instance;
	}
	
	//rank table에 새로운 유저를 추가한다.
	public void addRank(String nickname) {
		try {
			sqlMap.insert("addRank",nickname);			
		} catch (Exception e) {			
			e.printStackTrace();
		}
	}
	
	//특정 유저의 최고학점 rank를 얻는다.
	@SuppressWarnings("unchecked")
	public int getGradeMaxRank(String nickname) {
		List<Integer> result = null;		
		try
		{
			result = sqlMap.queryForList("getGradeMaxRank", nickname);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}		
		return result.get(0);
	}	
	
	//특정 유저의 최고학점 rank를 set한다.
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void setGradeMaxRank(String nickname,int gradeMaxRank) {				
		try
		{
			Map m = new HashMap();
			m.put("nickname", nickname);
			m.put("gradeMaxRank", gradeMaxRank);
			sqlMap.update("setGradeMaxRank", m);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}		
	}
	
	//특정유저의 최고학점 rank를 계산한다.( userscore table을 통해)
	@SuppressWarnings("unchecked")
	public ArrayList<String> evalGradeMaxRank() {
		ArrayList<String> result = null;		
		try
		{
			result = (ArrayList<String>)sqlMap.queryForList("evalGradeMaxRank");			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}		
		return result;
	}
}
