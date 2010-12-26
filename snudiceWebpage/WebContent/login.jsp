<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="/snudiceWebpage/css/loginPageStyle.css"/>
<title>로그인 페이지</title>
</head>
<body>
	<div class="header" id="loginHeader">
		TODO : 타이틀 이미지
	</div>
	<br/>
	<div class="container" id="loginContainer">
		<div class="left">&nbsp;</div>
		<div class="center" id="loginCenter">
			<form method="post" action="/snudiceWebpage/login.do">
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;				
				<span><img height="20" src="/snudiceWebpage/image/id.png"/></span>
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input  type="text" name="userId" tabindex="1"><br/>
				<img height="20" src="/snudiceWebpage/image/password.png"/>
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input type="password" name ="password" tabindex="2"><br/><br/>
				<input id="loginButton" type="image" src="/snudiceWebpage/image/gameStart.png" tabindex="2">							
			</form>
			
			<a href="/snudiceWebpage/clientFile/update/6001/a.txt">클라이언트 다운로드</a>
			
		</div>
		<div class="right">&nbsp;</div>	
	</div>
	
	<div class="footer" id="loginFooter">		
		* <a class="highlight" href="/snudiceWebpage/join.jsp">회원가입</a>
        | <a class="highlight" href="/snudiceWebpage/notimplemented.jsp">아이디, 비밀번호찾기</a>
	</div>		
</body>
</html>