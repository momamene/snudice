<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon">  
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/md5.js"></script> 
<script type="text/javascript" src="${root}/javascript/header.js"></script>
<script type="text/javascript" src="${root}/javascript/menuScript.js"></script> 
<script type="text/javascript" src="${root}/javascript/login.js"></script>
<link rel="stylesheet" type="text/css" href="${root}/css/commonStyle.css">
<link rel="stylesheet" type="text/css" href="${root}/css/loginModuleStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/menuStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/gameIntro.css">
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
<title>게임 시스템</title>
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
					<div class="contentTitle">게임 시스템</div>
					<div class="frameTop"></div>
					<div class="frameBody">
						<div id="system">
							<img src="${root}/image/misc/system.jpg"/>
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