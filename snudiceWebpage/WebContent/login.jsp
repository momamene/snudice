<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css"/>
<title>로그인 페이지</title>
</head>
<body>
	<div class="wrapper">
		<div class="header" id="loginHeader">
			<img src="${root}/image/mainpage/title.png"/>
		</div>
		<div class="container" id="loginContainer">
			<div class="left">
				<div class="leftTop">
					<br/><br/>
					<form method="POST" action="login.do">
						<div class="idpwWrap">
							<div class="idpw">
								<input name="userId" type="text"><br/>
								<input name="password" type="password">
							</div>
							<input id="login" type="image" src="${root}/image/mainpage/login.png">
						</div>
					</form>	
					<div class="loginHelp">
						<a href = "${root}/join.jsp">회원가입</a>&nbsp;&nbsp;&nbsp;&nbsp;<a href = "${root}/notimplemented.jsp"> ID/PW찾기</a><br/>
					</div>
				</div>
				<div class="leftBottom">
					<br/>
					&nbsp;&nbsp;&nbsp;&nbsp;
					<img src="${root}/image/mainpage/start.png">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<a href="${root}/clientFile/update/6001/a.txt"><img src="${root}/image/mainpage/download.png"></a>
				</div>
			</div>
			<div class="center" id="loginCenter">
				<jsp:include page = "/articleList.do" />   
			</div>
			<div class="right">&nbsp;</div>	
		</div>
		<div class="footer" id="loginFooter">		
		</div>			
	</div>
</body>
</html>