package dbaccess;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
	
	//특정 게시판의 pageNumber 에 해당하는 글을 articlePerPage 개수만큼 가져온다.
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public List<ArticleInfo> getArticleList(String boardName, int pageNumber, int articlePerPage) {
		List<ArticleInfo> result = null;
		try
		{			
			int maxArticleIndex = (Integer)sqlMap.queryForObject("getMaxArticleIndex");
			
			//해당 게시판의 가장 최근글의 index를 가져온다.
			Map m = new HashMap();
			m.put("boardName", boardName);
			m.put("startArticleIndex",maxArticleIndex);			
			result = sqlMap.queryForList("getArticleList", m);	
			int firstArticleIndex = result.get(0).getArticleIndex();
			
			int skipArticleCount = pageNumber * articlePerPage;
			
			m.remove("startArticleIndex");			
			m.put("startArticleIndex",firstArticleIndex );
			result = sqlMap.queryForList("getArticleList", m,skipArticleCount,articlePerPage);
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

	//새로운 글을 등록한다.
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

	//index로 글을 가져온다.
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

	//글을 수정한다.
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

	//조회수를 갱신한다.
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
	
	//글을 삭제한다.
	public void deleteArticle(int articleIndex) {
		try
		{
			sqlMap.delete("deleteArticle", articleIndex);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}	
}
