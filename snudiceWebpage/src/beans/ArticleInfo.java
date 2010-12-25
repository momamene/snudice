package beans;

import java.text.SimpleDateFormat;
import java.util.Date;

public class ArticleInfo {
	private int articleIndex;
	private String boardName;
	private String title;
	private String userId;
	private String dateTime;
	private String text;
	private int readCount;
	
	public ArticleInfo() {}
	
	public ArticleInfo(String boardName,String id, String title, String content,
			Date today) {
		
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String formatDate = dateFormat.format(today);
		
		this.boardName= boardName;
		this.userId = id;
		this.title = title;
		this.dateTime = formatDate;
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
	public void setTitle(String title) {
		this.title = title;
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
	public void setText(String text) {
		this.text = text;
	}
	public void setReadCount(int readCount) {
		this.readCount = readCount;
	}
	public int getReadCount() {
		return readCount;
	}
}