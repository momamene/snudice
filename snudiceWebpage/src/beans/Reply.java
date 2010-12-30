package beans;

public class Reply {
	private int replyIndex;
	private int articleIndex;
	private String userId;
	private String dateTime;
	private String replyText;
	
	public void setReplyIndex(int replyIndex) {
		this.replyIndex = replyIndex;
	}
	public int getReplyIndex() {
		return replyIndex;
	}
	public void setArticleIndex(int articleIndex) {
		this.articleIndex = articleIndex;
	}
	public int getArticleIndex() {
		return articleIndex;
	}
	public void setUserId(String userId) {
		this.userId = userId;
	}
	public String getUserId() {
		return userId;
	}
	public void setDateTime(String dateTime) {
		this.dateTime = dateTime;
	}
	public String getDateTime() {
		return dateTime;
	}
	public void setReplyText(String replyText) {
		this.replyText = replyText;
	}
	public String getReplyText() {
		return replyText;
	}
	
	
}
