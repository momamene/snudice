<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon">  
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/md5.js"></script> 
<script type="text/javascript"> 
<jsp:include page="/javascript/login.jsp"/>
</script>

<title>SNUDice Web Page에 오신 것을 환영합니다.</title>
</head>
<body>	
	<div class="bodyWrapper">		
		<jsp:include page="/reuseModule/headerModule.jsp"/>
		
		<div class="container">		
			<!-- menu -->
			<div id="menu">
				<div id="logoWrapper"></div>					
				<div id="logo"></div>
				<div id="menuWrapper">
					<div id="menu1">
						소식
						<div id="menu1DropDown" class="menuDropDownWrapper invisible">
							<div id="notice">								
								<a href="${root}/board/articleList.do?boardName=${noticeBoardName}&currPage=0">${noticeBoardAliasName}</a>								
							</div>
							<div id="update">								
								<a href="${root}/board/articleList.do?boardName=${updateBoardName}&currPage=0">${updateBoardAliasName}</a>							
							</div>							
						</div>
					</div>
					<div id="menu2">
						게임소개
						<div id="menu2DropDown" class="menuDropDownWrapper invisible">
							<div id="synopsis">시놉시스</div>
							<div id="playGuide">게임방법</div>
							<div id="character">캐릭터</div>
							<div id="card">카드</div>							
						</div>
					</div>
					<div id="menu3">
						PrjN
						<div id="menu3DropDown" class="menuDropDownWrapper invisible">
							<div id="teamIntro">팀소개</div>													
						</div>
					</div>
					<div id="menu4">
						게시판
						<div id="menu4DropDown" class="menuDropDownWrapper invisible">
							<div id="freeBoard">
								<a href="${root}/board/articleList.do?boardName=${freeBoardName}&currPage=0">${freeBoardAliasName}</a>
							</div>																		
						</div>
					</div>
					<div id="menu5">
						자료실
						<div id="menu5DropDown" class="menuDropDownWrapper invisible">
							<div id="gameDownload">	
								<a href="${root}/setupFile/SNUDiCE_setup.exe">게임 다운로드</a>										
							</div>
							<div id="wallPaper">월페이퍼</div>	
							<div id="screenShot">스크린샷</div>							
						</div>
					</div>
				</div>				
			</div>			
				
			<div class="containerTop"></div>		
			<div class="leftCenterRightWrapper">				
				<div class="left">
					<!--  회원가입 Form -->					
					<div id="joinFormWrapper" class="display_none">	
						<div id="joinTitle">회원가입</div>																
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
					
						<div id="joinMsg"></div>
						<span id="joinSubmit">가입하기</span>					
						<span id="joinClose">닫기</span>						
					</div>
					
					<!-- 로그인 Form -->
					<c:choose>
						<c:when test="${not empty userId}">
							<c:set var="loginFormWrapperClass" value="invisible"/>	
							<c:set var="mainLeftTopClass" value="loggined"/>
						</c:when>
						<c:otherwise>
							<c:set var="loginFormWrapperClass" value="visible"/>	
							<c:set var="mainLeftTopClass" value="logouted"/>
						</c:otherwise>
					</c:choose>
					
					<div id="mainLeftTop" class="${mainLeftTopClass}">						
						<div id="loginFormTitle" class="${loginFormWrapperClass}">	
							&nbsp;&nbsp;회원로그인					
							<div id="guestLogin"></div> 
						</div>		
						
						<div id="loginFormWrapper" class="${loginFormWrapperClass}">									
							<div id="idpw">
								ID<input id="userId" name="userId" type="text"/><br/>
								PW<input id="password" name="password" type="password"/>
							</div>					
							<div id="loginButton" class="mouseOut"></div>
													
							<div id="loginHelp">
								<hr/>												
								<a id="joinOpen" href="#">빠른 회원가입</a>							
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
						<a href="${root}/setupFile/SNUDiCE_setup.exe">게임 다운로드</a>										
					</div>
				</div>			
				<div id="centerContent" class="center">	
					<div id="centerL">
						<div id="centerLU">
							<span class="title">${noticeBoardAliasName}</span>
							<a href="${root}/board/articleList.do?boardName=${noticeBoardName}&currPage=0">
								<span class="centerLMore">더보기</span>
								<img src="${root}/image/mainpage/more.png"/>
							</a>
							<hr/>			
							<c:forEach var="article" items="${noticeList}">
								<img src="${root}/image/mainpage/noticeIcon.png"/>
								<span class="articleIcon">
									<a href="${root}/board/articleView.do?boardName=${noticeBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>
								</span>						
							</c:forEach>				
						</div>
						<div id="centerLD">							
							<span class="title">${updateBoardAliasName}</span>
							<a href="${root}/board/articleList.do?boardName=${updateBoardName}&currPage=0">							
								<span class="centerLMore">더보기</span>
								<img src="${root}/image/mainpage/more.png"/>
							</a>
							<hr/>			
							<c:forEach var="article" items="${updateList}">
								<img src="${root}/image/mainpage/updateIcon.png"/>
								<span class="articleIcon">
									<a href="${root}/board/articleView.do?boardName=${updateBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>
								</span>							
							</c:forEach>
						</div>						
					</div>					
					<div id="centerR">	
						<div id="centerRU">
							<span class="title">게임 가이드</span>							
							<hr/>											
						</div>
						<div id="centerRD">							
							<span class="title">팀소개</span>
							<hr/>							
						</div>	
					</div>						
				</div>
				<div class="right">&nbsp;</div>					
			</div>
			<div class="containerBottom"></div>						
		</div>		
		
		<jsp:include page="/reuseModule/footerModule.jsp"/>
		
	</div>
</body>
</html>