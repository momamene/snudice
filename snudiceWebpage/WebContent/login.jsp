<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon">  
<link rel="stylesheet" type="text/css" href="${root}/css/commonStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/loginModuleStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/menuStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css"/>
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/md5.js"></script> 
<script type="text/javascript" src="${root}/javascript/menuScript.js"></script> 
<script type="text/javascript" src="${root}/javascript/login.js"></script> 
<script type="text/javascript"> 
var root = "${root}";
window.onload = function() {
	initMenu();
	initLogin();
};

var _userId = "${userId}";
var _role = "${role}";
</script>

<title>SNUDice Web Page에 오신 것을 환영합니다.</title>
</head>
<body>	
	<div class="bodyWrapper">		
		<%@ include file="/reuseModule/headerModule.jsp"%>
		
		<div class="container">		
			<%@ include file="/reuseModule/menuModule.jsp"%>					
					
			<div class="leftCenterRightWrapper">				
				<div class="left">
					<%@ include file="/reuseModule/loginModule.jsp"%>
				
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
							<table class="articleTable">
								<c:forEach var="article" items="${noticeList}">	
									<tr>
										<td>
											<img class="articleIcon" src="${root}/image/mainpage/noticeIcon.png"/>
										</td>
										<td>										
											<a href="${root}/board/articleView.do?boardName=${noticeBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a>											
										</td>
									</tr>												
							</c:forEach>
							</table>							
																
						</div>
						<div id="centerLD">							
							<span class="title">${updateBoardAliasName}</span>
							<a href="${root}/board/articleList.do?boardName=${updateBoardName}&currPage=0">							
								<span class="centerLMore">더보기</span>
								<img src="${root}/image/mainpage/more.png"/>
							</a>
							<hr/>			
							<table class="articleTable">
								<c:forEach var="article" items="${updateList}">						
									<tr>
										<td>
											<img class="articleIcon" src="${root}/image/mainpage/updateIcon.png"/>										
										</td>
										<td>
											<a href="${root}/board/articleView.do?boardName=${updateBoardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a>										
										</td>
									</tr>																				
								</c:forEach>
							</table>	
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
		
		<%@ include file="/reuseModule/footerModule.jsp"%>
		
	</div>
</body>
</html>