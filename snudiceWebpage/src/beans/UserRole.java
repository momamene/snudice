package beans;

public class UserRole {
	private String userId;
	private String role;
	
	public UserRole() {}
	
	public UserRole(String userId, String role) {
		this.userId = userId;
		this.role = role;
	}
	public void setUserId(String userId) {
		this.userId = userId;
	}
	public String getUserId() {
		return userId;
	}
	public void setRole(String role) {
		this.role = role;
	}
	public String getRole() {
		return role;
	}
}
