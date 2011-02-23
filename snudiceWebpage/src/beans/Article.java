package beans;

import java.io.UnsupportedEncodingException;

import utility.Util;

public class Article {
	private int articleIndex;
	private String boardName;
	private byte[] title;
	private String nickname;
	private String dateTime;
	private byte[] text;
	private int readCount;
	private boolean rawStr; //html mode 지원을 위한 변수
	
	public Article() {}
	
	public Article(String boardName,String nickname, String title, String content) {		
		this.boardName= boardName;
		this.nickname = nickname;		
		this.dateTime = Util.currDateTime();		
		try {
			this.title = title.getBytes("utf-8");
			this.text = content.getBytes("utf-8");
		} catch (UnsupportedEncodingException e) {			
			e.printStackTrace();
		}
		this.rawStr = false;
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
		result += nickname;
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
		String result = null;
		try {
			result = new String(title,"utf-8");	
			if(!isRawStr())			
				result = Util.encodeHtml(result);
		}
		catch (UnsupportedEncodingException e) {			
			e.printStackTrace();
		}
		
		return result;
	}
	public void setTitle(byte[] title) {
		this.title = title;
	}
	public String getNickname() {
		return nickname;
	}
	public void setNickname(String nickname) {
		this.nickname = nickname;
	}
	public String getDateTime() {
		return dateTime;
	}
	public void setDateTime(String dateTime) {		
		this.dateTime = dateTime;
	}
	public String getText() {
		String result = null;
		try {
			result = new String(text,"utf-8");	
			if(!isRawStr())			
				result = Util.encodeHtml(result);
		}
		catch (UnsupportedEncodingException e) {			
			e.printStackTrace();
		}
		
		return result;
	}
	
	public void setText(byte[] text) {		
		this.text = text;
	}
	public void setReadCount(int readCount) {
		this.readCount = readCount;
	}
	public int getReadCount() {
		return readCount;
	}

	public void setRawStr(boolean rawStr) {
		this.rawStr = rawStr;
	}

	public boolean isRawStr() {
		return rawStr;
	}
}