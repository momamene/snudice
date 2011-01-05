<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript" src="${root}/javascript/login.js"></script>

<title>SNUDice Web Page에 오신 것을 환영합니다.</title>
</head>
<body>
	<div class="bodyWrapper">
		<div class="header">
			<div id="headerImage"></div>			
		</div>
		
		<div class="container">		
			<div class="left">
				<div id="joinFormWrapper" class="display_none">	
					<div class="centerAlign">회원가입</div>
					<hr/>
					<table id="joinFormTable">
						<tr>
							<td class="label">ID</td>
							<td><input id="joinId" type="text" maxlength="16" name="id"/></td>
						</tr>
						<tr>
							<td class="label">PW</td>
							<td><input id="joinPw" type="password" maxlength="255" name="pw"/></td>
						</tr>
						<tr>
							<td class="label">PW확인</td>
							<td><input id="joinPwConfirm" type="password" maxlength="255" name="pwConfirm"/></td>
						</tr>
						<tr>
							<td class="label">email</td>
							<td><input id="joinEmail" type="text" maxlength="255" name="email"/></td>
						</tr>
					</table>								
				
					<input id="joinSubmit" type="submit" value="가입하기"/>					
					<input id="joinClose" type="button" value="닫기"/>
					<div id="joinMsg"></div>
				</div>
				<div id="mainLeftTop">
					<div id="loginFormTitle">회원로그인</div>								
					<c:choose>
						<c:when test="${not empty userId}">
							<div id="loginFormWrapper" class="invisible">		
						</c:when>
						<c:otherwise>
							<div id="loginFormWrapper" class="visible">	
						</c:otherwise>
					</c:choose>											
						<div id="idpw">
							<input id="userId" name="userId" maxlength="16" type="text"/><br/>
							<input id="password" name="password" maxlength="255" type="password"/>
						</div>					
						<div id="loginButton" class="mouseOut"></div>
						<hr id="loginFormHorzLine"/>	
						<div id="loginHelp">												
							<a id="joinOpen" href="#">회원가입</a>							
							<a id="findIdPw" href="#">ID/PW찾기</a>
						</div>						
					</div>
					<c:choose>
						<c:when test="${not empty userId}">
							<div id="loginMsg" class="loggined">
						</c:when>	
						<c:otherwise>
							<div id="loginMsg" class="logouted">
						</c:otherwise>											
					</c:choose>	
					
					<c:choose>
						<c:when test="${not empty userId}">
							${userId} 님 로그인 하셨습니다.
						</c:when>												
					</c:choose>	
					</div>
					<c:choose>
						<c:when test="${not empty userId}">
							<div id="logoutWrapper" class="visible">		
						</c:when>
						<c:otherwise>
							<div id="logoutWrapper" class="invisible">	
						</c:otherwise>
					</c:choose>							
					</div>						
				</div>
				<div id="mainLeftBottom">					
					<div id="gameStart" onclick="alert('이건 없애야돼!');"></div>
					<div id="clientDownload" onclick="alert('클라 다운시켜!');"></div>					
				</div>
			</div>			
			<div class="center">			
				<div id="boardSelect">
					<br/>
					<c:forEach var="board" items="${boardList}">
						<a href="${root}/board/articleList.do?boardName=${board.boardName}&currPage=0">${board.aliasName}</a>&nbsp;|&nbsp;
					</c:forEach>
				</div>				
				<div id="centerLU">
					<span>공지사항</span>
					<hr/>			
					<c:forEach var="article" items="${noticeList}">
						<a href="${root}/board/articleView.do?boardName=${noticeBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>						
					</c:forEach>				
				</div>
				<div id="centerRU">
					<span>이벤트</span>
					<hr/>			
					<c:forEach var="article" items="${eventList}">
						<a href="${root}/board/articleView.do?boardName=${eventBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>						
					</c:forEach>
				</div>
				<div id="centerLD">
					<span>개발자노트</span>
					<hr/>			
					<c:forEach var="article" items="${devNoteList}">
						<a href="${root}/board/articleView.do?boardName=${devNoteBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>						
					</c:forEach>
				</div>				
				<div id="centerRD">
					<span>업데이트</span>
					<hr/>			
					<c:forEach var="article" items="${updateList}">
						<a href="${root}/board/articleView.do?boardName=${updateBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>						
					</c:forEach>
				</div>			
			</div>
			<div class="right">&nbsp;</div>				
		</div>		
		
		<div class="footer">		
		<hr/>PrjN
		</div>			
	</div>
</body>
</html>