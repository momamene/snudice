<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
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
							<td><input id="joinId" type="text" name="id"/></td>
						</tr>
						<tr>
							<td class="label">PW</td>
							<td><input id="joinPw" type="password" name="pw"/></td>
						</tr>
						<tr>
							<td class="label">PW확인</td>
							<td><input id="joinPwConfirm" type="password" name="pwConfirm"/></td>
						</tr>
						<tr>
							<td class="label">email</td>
							<td><input id="joinEmail" type="text" name="email"/></td>
						</tr>
					</table>								
				
					<input id="joinSubmit" type="submit" value="가입하기"/>					
					<input id="joinClose" type="button" value="닫기"/>
					<div id="joinMsg"></div>
				</div>
				<div id="mainLeftTop">
					<c:choose>
						<c:when test="${not empty userId}">
							<c:set var="loginFormWrapperClass" value="invisible"/>	
						</c:when>
						<c:otherwise>
							<c:set var="loginFormWrapperClass" value="visible"/>	
						</c:otherwise>
					</c:choose>
					
					<div id="loginFormTitle" class="${loginFormWrapperClass}">
						회원로그인
						<input id="guestLogin" type="button" value="손님로그인"/> 
					</div>		
					
					<div id="loginFormWrapper" class="${loginFormWrapperClass}">									
						<div id="idpw">
							<input id="userId" name="userId" type="text"/><br/>
							<input id="password" name="password" type="password"/>
						</div>					
						<div id="loginButton" class="mouseOut"></div>
												
						<div id="loginHelp">
							<hr class="hr1"/>												
							<a id="joinOpen" href="#">회원가입</a>							
							<a id="findIdPw" href="#">ID/PW찾기</a>
						</div>						
					</div>
					<c:choose>
						<c:when test="${not empty userId}">
							<c:set var="loginMsgClass" value="loggined"/>
						</c:when>	
						<c:otherwise>
							<c:set var="loginMsgClass" value="logouted"/>
						</c:otherwise>											
					</c:choose>	
					
					<div id="loginMsg" class="${loginMsgClass}">
						<c:choose>
							<c:when test="${not empty userId}">
								${userId} 님 로그인 하셨습니다.
							</c:when>												
						</c:choose>	
					</div>
					<c:choose>
						<c:when test="${not empty userId}">
							<c:set var="logoutWrapperClass" value="visible"/>		
						</c:when>
						<c:otherwise>
							<c:set var="logoutWrapperClass" value="invisible"/>		
						</c:otherwise>
					</c:choose>			
					<div id="logoutWrapper" class="${logoutWrapperClass}">				
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
		
		<div class="footer centerAlign">		
			<hr/>PrjN
		</div>			
	</div>
</body>
</html>