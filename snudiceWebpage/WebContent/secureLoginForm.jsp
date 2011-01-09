<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript">

window.onload = init;

function init()
{
	window.onresize = function()
	{
		windowAutoResize(1024);
	}	
	
	//header image 클릭시
	var secureLoginFormHeaderImage = document.getElementById("secureLoginFormHeaderImage");
	secureLoginFormHeaderImage.onclick = function() 
	{ 
		window.location = "${root}";		
	}
	
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
		<div class="header">
			<div id="secureLoginFormHeaderImage"></div>			
		</div>
		
		<div class="container">	
			<div class="left"></div>
					
			<div class="center_">
				<div id="mainLeftTop_">
					<div id="loginFormTitle" class="visible">
						회원로그인
						<input id="guestLogin" type="button" value="손님로그인"/> 
					</div>
					
					<div id="loginFormWrapper" class="visible">
						<form id="secureloginForm" method="POST" action="j_security_check">
							<div id="idpw">	
								<input id="userId" type="text" name="j_username"><br/>		
								<input id="password" type="password" name="j_password"><br/>	
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
		
		<div class="footer centerAlign">
			<hr class="lightColor marginZero"/>${footerMsg}
		</div>
	
	</div>
</body>
</html>