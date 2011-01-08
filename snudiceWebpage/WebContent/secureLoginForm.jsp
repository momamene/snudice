<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript">
window.onload = init;

function init()
{
	//손님 로그인 버튼
	var guestLogin = document.getElementById("guestLogin");
	guestLogin.onclick = guestLoginFunc;
	
	//패스워드 창에서 엔터 치면 로그인시킴
	enterKeyExec("password",loginFunc);
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

<title>로그인이 필요합니다.</title>
</head>
<body>
	<div class="bodyWrapper">
		<div class="header">
			<div id="headerImage"></div>			
		</div>
		
		<div class="container">	
			<div class="left"></div>
			
			<div class="center">
				<form id="loginForm" method="POST" action="j_security_check">		
					<input id="userId" type="text" name="j_username"><br/>		
					<input id="password" type="password" name="j_password"><br/>		
					<input type="image" src="/snudiceWebpage/image/mainpage/login.png">
					<input id="guestLogin" type="button" value="손님로그인"/> 
				</form>	
			</div>
			
			<div class="right"></div>
		</div>
		
		<div class="footer">
			<hr/>PrjN
		</div>
	
	</div>
</body>
</html>