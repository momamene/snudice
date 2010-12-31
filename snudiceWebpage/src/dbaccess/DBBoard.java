package dbaccess;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import utility.Util;

import beans.Article;
import beans.Board;
import beans.Auth;
import beans.Reply;

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
	public List<Article> getArticleList(String boardName, int pageNumber, int articlePerPage) {
		List<Article> result = null;
		try
		{			
			int maxArticleIndex = (Integer)sqlMap.queryForObject("getMaxArticleIndex");
			
			//해당 게시판의 가장 최근글의 index를 가져온다.
			Map m = new HashMap();
			m.put("boardName", boardName);
			m.put("startArticleIndex",maxArticleIndex);			
			result = sqlMap.queryForList("getArticleList", m);	
			if(result.size()==0) //글이 하나도 없는 경우
				return result;
			
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
	public int insertArticle(Article article) {
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
	public Article getArticleByIndex(int articleIndex) {
		Article result=null;
		try
		{
			 result= (Article) sqlMap.queryForObject("getArticleByIndex", articleIndex);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return result;		
	}

	//글을 수정한다.
	public int updateArticle(Article article) {
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

	//댓글을 삽입한다.
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void insertReply(int articleIndex, String userId, String replyText) {
		try
		{
			HashMap m = new HashMap();
			m.put("articleIndex", articleIndex);
			m.put("userId", userId);
			m.put("dateTime", Util.currDateTime());
			m.put("replyText", replyText);
			sqlMap.insert("insertReply", m);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}		
	}

	//특정 글에 달린 댓글들을 가져온다.
	@SuppressWarnings("unchecked")
	public List<Reply> getReplyList(int articleIndex) {
		List<Reply> result = null;
		
		try
		{
			result = sqlMap.queryForList("getReplyList", articleIndex);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return result;
	}	
	
	//특정 글에 달린 댓글의 개수를 가져온다.
	public int getReplyCount(int articleIndex)	{
		Integer result = null;
		
		try
		{
			result = (Integer)sqlMap.queryForObject("getReplyCount", articleIndex);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return result;
	}
	
	//게시판 목록을 가져온다.
	@SuppressWarnings("unchecked")
	public List<Board> getBoardList() {
		List<Board> result = null;
		
		try
		{			
			result = (List<Board>)sqlMap.queryForList("getBoardList");			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return result;	
	}	
	
	//게시판 접근 권한 정보를 가져온다.
	@SuppressWarnings("unchecked")
	public Auth getBoardAuth(String boardName) {
		List<Auth> result = null;
		
		try
		{			
			result = (List<Auth>)sqlMap.queryForList("getBoardAuth",boardName);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return result.get(0);
	}

	//게시판을 삭제한다.
	public void deleteBoard(String boardName) {
		try
		{
			//댓글 삭제
			sqlMap.delete("allDeleteReply",boardName);
			//글삭제
			sqlMap.delete("allDeleteArticle",boardName);
			//권한 정보 삭제
			sqlMap.delete("deleteBoardAuth",boardName);
			//게시판삭제	
			sqlMap.delete("deleteBoard",boardName);			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}				
	}
}
