<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="stylesheet" type="text/css" href="${root}/css/secureLoginForm.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/md5.js"></script>
<script type="text/javascript">
<jsp:include page="/javascript/header.jsp"/>
</script>  
<script type="text/javascript">

<!-- 앞에서 include 한 내용의 일부는 덮어써진다. -->
window.onload = init;

function init()
{	
	initHeader();
	
	//로그인 버튼
	var loginButton = document.getElementById("loginButton");
	loginButton.onclick = loginFunc;
	loginButton.onmouseover = mousOverFunc;
	loginButton.onmouseout = mouseOutFunc;
	
	//패스워드 창에서 엔터 치면 로그인시킴
	enterKeyExec("password",loginFunc);
	
	//손님 로그인 버튼
	var guestLogin = document.getElementById("guestLogin");
	guestLogin.onclick = guestLoginFunc;
	
	//로그인 실패시
	if("${param.fail}"!="")
	{
		var userId = document.getElementById("userId");
		userId.focus();
	}
}

function guestLoginFunc()
{
	var userId = document.getElementById("userId");
	userId.value = "guest";
	var password = document.getElementById("password");
	password.value = "guest";
	loginFunc();
}

function loginFunc()
{
	var userId = document.getElementById("userId");
	var password = document.getElementById("password");
	var loginMsg = document.getElementById("loginMsg");	

	//validation
	if(userId.value=="")
	{
		loginMsg.innerHTML = "id를 입력해 주세요";
		userId.focus();
		return;
	}
	if(password.value=="")
	{
		loginMsg.innerHTML = "password를 입력해 주세요";
		password.focus();
		return;
	}	

	loginMsg.innerHTML = "로그인 중입니다..";
	
	password.value = MD5(password.value);
	var secureloginForm = document.getElementById("secureloginForm");
	secureloginForm.submit();
}

//마우스를 올려놓는 경우
function mousOverFunc()
{
	this.className = "mouseOver";	
}

//마우스를 떼는 경우
function mouseOutFunc()
{
	this.className = "mouseOut";
}

</script>

<title>로그인이 필요합니다.</title>
</head>
<body>
	<div class="bodyWrapper">
		<jsp:include page="/reuseModule/headerModule.jsp"/>
		
		<div class="container">	
			<div class="left"></div>
					
			<div class="center">
				<div id="mainLeftTop">
					<div id="loginFormTitle" class="visible">
						&nbsp;&nbsp;&nbsp;회원로그인
						<div id="guestLogin"></div> 
					</div>
					
					<div id="loginFormWrapper">
						<form id="secureloginForm" method="POST" action="j_security_check">
							<div id="idpw">	
								ID<input id="userId" type="text" name="j_username"><br/>		
								PW<input id="password" type="password" name="j_password"><br/>	
							</div>							
							<div id="loginButton" class="mouseOut"></div>
						</form>	
					</div>												
					<div id="loginMsg" class="visible clearLeft">
						<c:if test="${not empty param.fail}">
							로그인 실패!							
						</c:if>
					</div>					
				</div>				
			</div>
			
			<div class="right"></div>
		</div>
		
		<jsp:include page="/reuseModule/footerModule.jsp"/>
	
	</div>
</body>
</html>