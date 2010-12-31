package beans;

public class Auth {	
	private String boardName;
	private String admin;
	private String manager;
	private String member;
	private String guest;
	
	@Override
	public String toString() {
		String result = "";		
		result += "boardName="+getBoardName();
		result += "\tadmin="+getAdmin();
		result += "\tmanager="+getManager();
		result += "\tmember="+getMember();	
		result += "\tguest="+getGuest();		
		return result;
	}

	public void setBoardName(String boardName) {
		this.boardName = boardName;
	}

	public String getBoardName() {
		return boardName;
	}

	public void setAdmin(String admin) {
		this.admin = admin;
	}

	public String getAdmin() {
		return admin;
	}

	public void setManager(String manager) {
		this.manager = manager;
	}

	public String getManager() {
		return manager;
	}

	public void setMember(String member) {
		this.member = member;
	}

	public String getMember() {
		return member;
	}

	public void setGuest(String guest) {
		this.guest = guest;
	}

	public String getGuest() {
		return guest;
	}	

	
}
