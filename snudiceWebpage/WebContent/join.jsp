<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="/snudiceWebpage/css/loginPageStyle.css"/>
<title>회원가입 페이지</title>
</head>
<body>
	<div class="header"></div>
	
	<div class="container">
		<div class="left"></div>
		<div class="center">
			<form action = "/snudiceWebpage/join.do" method = "post">
				아이디 : <input type = "text" name="userId"> <br/>
				패스워드 : <input type = "password" name="password"> <br/>	
				e-mail : <input type = "text" name="email"> <br/>	
				<input type = "submit" value = "가입하기">
			</form>
		</div>
		<div class="right"></div>
	</div>
	
</body>
</html>

