<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="/godwar/css/loginPageStyle.css"/>
<title>회원가입 페이지</title>
</head>
<body>
	<form action = "join.do" method = "post">
		아이디 : <input type = "text" name="userId"> <br/>
		패스워드 : <input type = "password" name="password"> <br/>
		신의종류 : 
		<input type = "radio" name="godKind" value="0"> 전쟁의 신
		<input type = "radio" name="godKind" value="1"> 포교의 신
		<input type = "radio" name="godKind" value="2"> 건설의 신
		<br/>
		
		<input type = "submit" value = "가입하기">
	</form>
</body>
</html>

