package beans;

public class Board {
	private String boardName;
	private String aliasName;
	
	@Override
	public String toString() {
		return boardName+"/"+aliasName;
	}	
	
	public void setBoardName(String boardName) {
		this.boardName = boardName;
	}
	public String getBoardName() {
		return boardName;
	}
	public void setAliasName(String aliasName) {
		this.aliasName = aliasName;
	}
	public String getAliasName() {
		return aliasName;
	}
}
