package beans;

public class BoardAuth {
	private String boardName;
	private String role;
	private boolean read;
	private boolean write;
	private boolean admin;
	
	@Override
	public String toString() {
		String result = "";
		result += "boardName="+boardName;
		result += "\trole="+role;
		result += "\tread="+read;
		result += "\twrite="+write;
		result += "\tadmin="+admin;		
		return result;
	}
	
	public void setBoardName(String boardName) {
		this.boardName = boardName;
	}
	public String getBoardName() {
		return boardName;
	}
	public void setRole(String role) {
		this.role = role;
	}
	public String getRole() {
		return role;
	}
	public void setRead(boolean read) {
		this.read = read;
	}
	public boolean isRead() {
		return read;
	}
	public void setWrite(boolean write) {
		this.write = write;
	}
	public boolean isWrite() {
		return write;
	}
	public void setAdmin(boolean admin) {
		this.admin = admin;
	}
	public boolean isAdmin() {
		return admin;
	}
}
