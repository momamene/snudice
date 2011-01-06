package beans;

import utility.Util;

public class Article {
	private int articleIndex;
	private String boardName;
	private String title;
	private String userId;
	private String dateTime;
	private String text;
	private int readCount;
	
	public Article() {}
	
	public Article(String boardName,String id, String title, String content) {		
		this.boardName= boardName;
		this.userId = id;
		this.title = title;
		this.dateTime = Util.currDateTime();
		this.text = content;
	}
	
	@Override
	public String toString() {
		String result = "";
		result += Integer.toString(articleIndex);
		result += "/";
		result += boardName;
		result += "/";
		result += title;
		result += "/";
		result += userId;
		result += "/";
		result += dateTime;
		result += "/";
		result += text;
		result += "/";
		result += readCount;
		
		return result;
	}
	
	public int getArticleIndex() {
		return articleIndex;
	}
	public void setArticleIndex(int articleIndex) {
		this.articleIndex = articleIndex;
	}
	public String getBoardName() {
		return boardName;
	}
	public void setBoardName(String boardName) {
		this.boardName = boardName;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(byte[] title) {
		try {
			this.title = Util.toHtml(new String(title,"utf-8"));
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	public String getUserId() {
		return userId;
	}
	public void setUserId(String userId) {
		this.userId = userId;
	}
	public String getDateTime() {
		return dateTime;
	}
	public void setDateTime(String dateTime) {		
		this.dateTime = dateTime;
	}
	public String getText() {
		return text;
	}
		
	public void setText(byte[] text) {
		try {
			this.text = Util.toHtml(new String(text,"utf-8"));
		}	
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	public void setReadCount(int readCount) {
		this.readCount = readCount;
	}
	public int getReadCount() {
		return readCount;
	}
}