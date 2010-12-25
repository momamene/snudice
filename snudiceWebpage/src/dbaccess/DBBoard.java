package dbaccess;

import java.util.List;
import beans.ArticleInfo;

import com.ibatis.sqlmap.client.SqlMapClient;

public class DBBoard {
	private volatile static DBBoard instance = null;
	private SqlMapClient sqlMap = null;
	
	private DBBoard(SqlMapClient sqlMap) {		
		this.sqlMap = sqlMap;
	}
	
	//DCL(Double-Checking Locking) 을 사용하여 동기화
	public static DBBoard getInstance(SqlMapClient sqlMap) {
		if(instance==null)
		{
			synchronized(DBBoard.class)
			{
				if(instance==null)
				{
					instance = new DBBoard(sqlMap);
				}
			}
		}
		return instance;
	}
	
	//특정 게시판의 startArticleIndex 번째 게시물 ~ endArticleIndex 번째 게시물 까지를 리턴함
	@SuppressWarnings("unchecked")
	public List<ArticleInfo> getArticleList(String boardName, int startArticleIndex, int endArticleIndex) {
		List<ArticleInfo> result = null;
		try
		{			
			result = sqlMap.queryForList("getArticleList", boardName,startArticleIndex, endArticleIndex);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return result;
	}
	
	//보드 네임을 받아, 전체 게시물의 갯수르
	public int getArticleCount(String boardName) {
		Integer result = null;
		
		try
		{
			result = (Integer) sqlMap.queryForObject("getArticleCount", boardName);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return result.intValue();
	}
	

	public int insertArticle(ArticleInfo article) {
		int result=-1;
		try
		{
			result=(Integer) sqlMap.insert("insertArticle", article);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}		
		return result;
	}

	//index를 전달하면 아티클에 대한 정보를 쿼리 해온다.
	public ArticleInfo getArticleByIndex(int articleIndex) {
		ArticleInfo result=null;
		try
		{
			 result= (ArticleInfo) sqlMap.queryForObject("getArticleByIndex", articleIndex);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return result;
		
	}

	public int updateArticle(ArticleInfo article) {
		int result=0 ;
		try
		{
			result= sqlMap.update("updateArticle", article);
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return result;
		
	}

	public void updateArticleReadCount(int articleIndex) {
		try
		{
			sqlMap.update("updateArticleReadCount", articleIndex);
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		
	}
}
