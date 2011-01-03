<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript">

window.onload = init;

//event handler 추가	
function init()
{		
	//가입창 열기 버튼	
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.onclick = joinOpenFunc;	
	//가입창  버튼
	var joinCloseButton = document.getElementById("joinClose");
	joinCloseButton.onclick = joinCloseFunc;
	//가입하기 버튼
	var joinSubmit = document.getElementById("joinSubmit");
	joinSubmit.onclick = joinSubmitFunc;
	//로그인 버튼
	var loginButton = document.getElementById("loginButton");
	loginButton.onclick = loginFunc;
}

////////////////////event handler/////////////////////

//회원 가입 창을 연다
function joinOpenFunc()
{	
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.disabled = true;
	
	var joinFormWrapper = document.getElementById("joinFormWrapper");		
	joinFormWrapper.className = "display_block";	
}

//회원 가입 창을 닫는다
function joinCloseFunc()
{			
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.disabled = false;
	
	var joinSubmit = document.getElementById("joinSubmit");
	joinSubmit.disabled = false;
	
	var joinFormWrapper = document.getElementById("joinFormWrapper");	
	var joinId = document.getElementById("joinId");
	var joinPw = document.getElementById("joinPw");
	var joinPwConfirm = document.getElementById("joinPwConfirm");
	var joinEmail = document.getElementById("joinEmail");
	var joinMsg = document.getElementById("joinMsg");

	joinId.value = "";
	joinPw.value = "";
	joinPwConfirm.value = "";
	joinEmail.value = "";
	joinMsg.innerHTML = "";
	
	joinFormWrapper.className = "display_none";
}

//회원 가입 요청을 보낸다
function joinSubmitFunc()
{	
	var joinId = document.getElementById("joinId");
	var joinPw = document.getElementById("joinPw");
	var joinPwConfirm = document.getElementById("joinPwConfirm");
	var joinEmail = document.getElementById("joinEmail");
	var joinSubmit = document.getElementById("joinSubmit");	

	var joinMsg = document.getElementById("joinMsg");
	
	//validation
	if(joinId.value=="")
	{
		joinMsg.innerHTML = "id를 입력해주세요.";
		joinId.focus();
		return;
	}
	if(joinPw.value=="")
	{
		joinMsg.innerHTML = "password를 입력해주세요.";
		joinPw.focus();
		return;
	}
	if(joinPwConfirm.value=="")
	{
		joinMsg.innerHTML = "password 확인란에 입력해 주세요.";
		joinPwConfirm.focus();
		return;
	}
	if(joinPw.value!=joinPwConfirm.value)
	{
		joinMsg.innerHTML = "password와 password 확인란이 일치하지 않습니다.";
		joinPwConfirm.focus();
		joinPwConfirm.select();
		return;
	}
	if(joinEmail.value=="")
	{
		joinMsg.innerHTML = "email을 입력해주세요";
		joinEmail.focus();
		return;
	}

	joinMsg.innerHTML = "가입처리중입니다...";
	joinSubmit.disabled = true;	
	
	var url = "${root}/join.ajax";	
	var method = "POST";
	var param = "joinId="+joinId.value;
	param += "&joinPw="+joinPw.value;	
	param += "&joinEmail="+joinEmail.value;
	var callback = joinFormRefresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);		
}

//로그인 요청을 보낸다.
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
	
	var url = "${root}/login.ajax";	
	var method = "POST";
	var param = "userId="+userId.value;
	param += "&password="+password.value;	
	var callback = loginFormRefresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);	
}

////////////////////callback function/////////////////////
function joinFormRefresh()
{		
	var joinId = document.getElementById("joinId");
	var joinPw = document.getElementById("joinPw");
	var joinEmail = document.getElementById("joinEmail");
	var joinSubmit = document.getElementById("joinSubmit");	
	var joinMsg = document.getElementById("joinMsg");

	if(request.readyState == 4)
	{		
		joinSubmit.disabled = false;
		
		if(request.status == 200)
		{				
			if(request.responseText == "idContainSpace")
			{
				joinMsg.innerHTML = "id는 공백문자를 포함할 수 없습니다.";
				joinId.focus();
				joinId.select();
			}				
			else if(request.responseText == "pwContainSpace")
			{
				joinMsg.innerHTML = "password는 공백문자를 포함할 수 없습니다.";
				joinPw.focus();
				joinPw.select();
			}	
			else if(request.responseText == "emailContainSpace")
			{
				joinMsg.innerHTML = "email은 공백문자를 포함할 수 없습니다.";
				joinEmail.focus();
				joinEmail.select();
			}				
			else if(request.responseText == "existingUser")
			{
				joinMsg.innerHTML = "이미 존재하는 id입니다.";
				joinId.focus();
				joinId.select();
			}						
				 
			if(request.responseText == "joinOK")
			{			
				alert("회원 가입이 완료되었습니다.");
				joinCloseFunc();
			}
		}
	}	
}

function loginFormRefresh()
{	
	var userId = document.getElementById("userId");	
	var loginMsg = document.getElementById("loginMsg");	
	var logoutWrapper = document.getElementById("logoutWrapper");		
	
	if(request.readyState == 4)
	{		
		if(request.status == 200)
		{			
			if(request.responseText=="loginOK")
			{
				loginMsg.innerHTML = userId.value + " 님 로그인 하셨습니다.";
				var loginFormWrapper = document.getElementById("loginFormWrapper");
				
				loginFormWrapper.className = "invisible";				
				logoutWrapper.className = "visible";				
			}
			else if(request.responseText=="loginFail")
			{				
				loginMsg.innerHTML = "로그인 실패!";
				userId.focus();
				userId.select();
			}
			else if(request.responseText=="alreadyLoggined")
			{
				loginMsg.innerHTML = "이미 로그인 되어있습니다.";
				logoutWrapper.className = "visible";
			}			
		}
	}	
}

function testFunc()
{	
	var url = "${root}/board/articleList.do?boardName=test&currPage=0";	
	//var url = "testAjax.ajax";	
	var method = "GET";
	var param = null;
	var callback = testCallback;
	var async = true;
	
	sendRequest(url,method,param,callback,async);	
}

function testCallback()
{
	if(request.readyState == 4)
	{
		if(request.status == 200)
		{	
			var test = document.getElementById("test");
			var responseXML = request.responseXML;			

			if(!window.DOMParser) //IE인 경우			
			{						
				responseXML = new ActiveXObject("Microsoft.XMLDOM");
				responseXML.async = "false";								
				responseXML.loadXML(request.responseText);
				responseXML = responseXML.documentElement;
				test.innerHTML = responseXML.getElementsByTagName("body")[0].xml;
			}	
			else
			{				
				test.innerHTML = responseXML.getElementsByTagName("body")[0].innerHTML;
			}			
		}
	}	
}

</script>

<title>SNUDice Web Page에 오신 것을 환영합니다.</title>
</head>
<body>
	<div class="wrapper">
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
					<br/><br/>		
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
						<div id="loginButton"></div>					
						<div id="loginHelp">
							<input id="joinOpen" type="button" value="회원가입"/>
							<a href = "${root}/notimplemented.jsp"> ID/PW찾기</a><br/>
						</div>
					</div>
					<div id="loginMsg">
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
						<a href="logout.do">로그아웃</a>	
					</div>						
				</div>
				<div id="mainLeftBottom">					
					<div id="gameStart" onclick="alert('이건 없애야돼!');"></div>
					<div id="clientDownload" onclick="alert('클라 다운시켜!');"></div>					
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
				<div id="notice">
					공지사항<br/><hr/>					
					<c:forEach var="article" items="${articleList}">
						<a href="${root}/board/articleView.do?boardName=${boardName}&articleIndex=${article.articleIndex}&currPage=0">${article.title}</a><br/>						
					</c:forEach>
				</div>
			</div>
			<div class="right">&nbsp;</div>				
		</div>		
		
		<div class="footer">		
		<hr/>
		PrjN<br/>
			<input type="button" onclick="testFunc();" value="test"/> 
			<div id="test"></div>				
		</div>			
	</div>
</body>
</html>