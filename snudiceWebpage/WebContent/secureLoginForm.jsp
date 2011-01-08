<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<script type="text/javascript">
window.onload = init;

function init()
{
	//손님 로그인 버튼
	var guestLogin = document.getElementById("guestLogin");
	guestLogin.onclick = guestLoginFunc;	
}

function guestLoginFunc()
{
	var userId = document.getElementById("userId");
	userId.value = "guest";
	var password = document.getElementById("password");
	password.value = "guest";
	var loginForm = document.getElementById("loginForm");
	loginForm.submit();
}

</script>

<title>보안 로그인</title>
</head>
<body>
	<form id="loginForm" method="POST" action="j_security_check">		
		<input id="userId" type="text" name="j_username"><br/>		
		<input id="password" type="password" name="j_password"><br/>		
		<input type="image" src="/snudiceWebpage/image/mainpage/login.png">
		<input id="guestLogin" type="button" value="손님로그인"/> 
	</form>
</body>
</html>