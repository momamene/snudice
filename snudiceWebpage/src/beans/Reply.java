package beans;

public class Reply {
	private int replyIndex;
	private int articleIndex;
	private String nickname;
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
	public void setNickname(String nickname) {
		this.nickname = nickname;
	}
	public String getNickname() {
		return nickname;
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
