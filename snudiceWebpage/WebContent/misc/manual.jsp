<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon">  

<link rel="stylesheet" type="text/css" href="${root}/css/commonStyle.css">
<link rel="stylesheet" type="text/css" href="${root}/css/loginModuleStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/menuStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/gameIntro.css">
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/md5.js"></script> 
<script type="text/javascript" src="${root}/javascript/header.js"></script>
<script type="text/javascript" src="${root}/javascript/menuScript.js"></script> 
<script type="text/javascript" src="${root}/javascript/login.js"></script> 
<script type="text/javascript"> 
var root = "${root}";
window.onload = function() {
	initHeader();
	initMenu();
	initLogin();
};

var _userId = "${userId}";
var _role = "${role}";
</script>
<title>게임방법</title>
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
									
					</div>					
				</div>
				
				<div class="center">
					<div class="contentTitle">게임 방법</div>	
					<div class="frameTop"></div>
					<div class="frameBody">
						<div id="manualSelect">
							<c:choose>
								<c:when test="${param.page==1}">
									<c:set var="manualPage1ClassName" value="selected"/>
									<c:set var="manualPage2ClassName" value="unSelected"/>
								</c:when>
								<c:when test="${param.page==2}">
									<c:set var="manualPage1ClassName" value="unSelected"/>
									<c:set var="manualPage2ClassName" value="selected"/>
								</c:when>
							</c:choose>	
							<div id="manualPageButtonWrapper">
								<div id="manualPage1Button" class="${manualPage1ClassName}">
									<a class="contentSmallTitle" href="${root}/misc/manual.do?page=1">게임 참여</a>
								</div>
								<div id="manualPage2Button" class="${manualPage2ClassName}">
									<a class="contentSmallTitle" href="${root}/misc/manual.do?page=2">게임 시작</a>
								</div>
							</div>							
						</div>
						
						<div id="manualContent">						
							<c:choose>
								<c:when test="${param.page==1}">
									<img src="${root}/image/misc/manualPage1.png"/>
								</c:when>	
								<c:when test="${param.page==2}">
									<img src="${root}/image/misc/manualPage2.jpg"/>
								</c:when>				
							</c:choose>
						</div>
					</div>
					<div class="frameBottom"></div>
				</div>
				
				<div class="right"></div>
				<div class="dummy"></div>
			</div>
			
			<div class="containerBottom"></div>
		</div>
		
		<%@ include file="/reuseModule/footerModule.jsp"%>
		
	</div>
</body>
</html>