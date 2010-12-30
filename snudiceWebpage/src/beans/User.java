package beans;

public class User {
	private String userId;
	private String password;
	private String email;
	
	public User() {}
	
	public User(String userId,String password,String email) {
		this.userId = userId;
		this.password = password;
		this.email = email;
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
}
