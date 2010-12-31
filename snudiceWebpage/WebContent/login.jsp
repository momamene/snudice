<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css"/>
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript">


</script>

<title>로그인 페이지</title>
</head>
<body>
	<div class="wrapper">
		<div class="header">
			<img src="${root}/image/mainpage/title.png"/>
		</div>
		
		<div class="container">		
			<div class="left">
				<div id="mainLeftTop">
					<br/><br/>
					<form method="POST" action="login.do">
						<div id="idpwWrap">
							<div id="idpw">
								<input name="userId" type="text" size="16px"><br/>
								<input name="password" type="password" size="16px">
							</div>
							<input id="login" type="image" src="${root}/image/mainpage/login.png">
						</div>
					</form>	
					<div id="loginHelp">
						<a href = "${root}/join.jsp">회원가입</a>&nbsp;&nbsp;&nbsp;&nbsp;<a href = "${root}/notimplemented.jsp"> ID/PW찾기</a><br/>
					</div>
				</div>
				<div id="mainLeftBottom">
					<br/>
					&nbsp;&nbsp;&nbsp;&nbsp;
					<img src="${root}/image/mainpage/start.png">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<a href="${root}/clientFile/update/6001/a.txt"><img src="${root}/image/mainpage/download.png"></a>
				</div>
			</div>			
			<div class="center">			
				<div id="boardSelect">
					<c:forEach var="board" items="${boardList}">
						<a href="${root}/board/articleList.do?boardName=${board.boardName}&currPage=0">${board.aliasName}</a>&nbsp;|&nbsp;
					</c:forEach>
				</div>
				<hr/>
				<div id="intro">
				TODO : 게임소개 등
				</div>
				<hr/>
				<div id="notice">
					공지사항<br/><hr/>					
					<c:forEach var="article" items="${articleList}">
						<a href="${root}/board/articleView.do?boardName=${boardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>						
					</c:forEach>
				</div>								
			</div>
			<div class="right"></div>				
		</div>
		
		<div class="footer" id="loginFooter">		
		</div>			
	</div>
</body>
</html>