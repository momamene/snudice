package beans;

public class User {
	private String userId;
	private String password;
	private String email;
	private String nickname;
	private String comment;
	private String activationCode; //가입 대기 중일 때 email 인증을 위해 사용
	private String role; //가입 대기중일 때 사용
	
	public User() {}
	
	public User(String userId,String password,String email,String nickname,String comment,String role) {
		this.userId = userId;
		this.password = password;
		this.email = email;
		this.nickname= nickname;
		this.comment = comment;
		this.role = role;
	}
	
	public User(String userId,String password,String email,String nickname,String comment,String activationCode,String role) {
		this.userId = userId;
		this.password = password;
		this.email = email;
		this.nickname= nickname;
		this.comment = comment;
		this.activationCode = activationCode;
		this.role = role;
	}
	
	public void setUserId(String userId) {
		this.userId = userId;
	}
	public String getUserId() {
		return userId;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getPassword() {
		return password;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getEmail() {
		return email;
	}

	public void setNickname(String nickname) {
		this.nickname = nickname;
	}

	public String getNickname() {
		return nickname;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}

	public String getComment() {
		return comment;
	}

	public void setActivationCode(String activationCode) {
		this.activationCode = activationCode;
	}

	public String getActivationCode() {
		return activationCode;
	}

	public void setRole(String role) {
		this.role = role;
	}

	public String getRole() {
		return role;
	}
}
