<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>로그인 해주세요</title>
</head>
<body> 
	<form method="POST" action="login.do">
		<img src="${root}/image/id.png"/>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<input type="text" name="userId"><br/>
		<img src="${root}/image/password.png"/>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<input type="password" name="password"><br/>		
		<input type="image" src="${root}/image/gameStart.png">
	</form>	
</body>
</html>