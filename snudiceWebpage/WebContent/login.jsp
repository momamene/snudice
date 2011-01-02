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

window.onload = init;

function init()
{	
	//event handler 추가	
	//가입창 열기 버튼	
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.onclick = joinOpenFunc;	
	//가입창  버튼
	var joinCloseButton = document.getElementById("joinClose");
	joinCloseButton.onclick = joinCloseFunc;
	//가입하기 버튼
	var joinSubmit = document.getElementById("joinSubmit");
	joinSubmit.onclick = joinSubmitFunc;
	
	var joinId = document.getElementById("joinId");
	//joinId.onblur = function() {alert("joinId onblur 발생");}
}

////////////////////event handler/////////////////////

//회원 가입 창을 연다
function joinOpenFunc()
{	
	var joinFormWrapper = document.getElementById("joinFormWrapper");	
	joinFormWrapper.style.display = "block";	
}

//회원 가입 창을 닫는다
function joinCloseFunc()
{			
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
	
	joinFormWrapper.style.display = "none";	
}

//회원 가입 요청을 보낸다
function joinSubmitFunc()
{	
	var joinId = document.getElementById("joinId").value;
	var joinPw = document.getElementById("joinPw").value;
	var joinPwConfirm = document.getElementById("joinPwConfirm").value;
	var joinEmail = document.getElementById("joinEmail").value;
	
	var url = "${root}/join.ajax";	
	var method = "POST";
	var param = "joinId="+joinId;
	param += "&joinPw="+joinPw;
	param += "&joinPwConfirm="+joinPwConfirm;
	param += "&joinEmail="+joinEmail;
	var callback = joinFormRefresh;
	var async = true;
	
	sendRequest(url,method,param,callback,async);		
}

////////////////////callback function/////////////////////
function joinFormRefresh()
{	
	var joinSubmit = document.getElementById("joinSubmit");	
	var joinMsg = document.getElementById("joinMsg");

	if(request.readyState == 4)
	{
		if(request.status == 200)
		{	
			if(request.responseText == "idEmpty")
				joinMsg.innerHTML = "id를 입력해주세요.";
			else if(request.responseText == "idContainSpace")
				joinMsg.innerHTML = "id는 공백문자를 포함할 수 없습니다.";
			else if(request.responseText == "pwEmpty")
				joinMsg.innerHTML = "password를 입력해주세요.";
			else if(request.responseText == "pwContainSpace")
				joinMsg.innerHTML = "password는 공백문자를 포함할 수 없습니다.";
			else if(request.responseText == "pwConfirmEmpty")
				joinMsg.innerHTML = "password 확인란에 입력해 주세요.";
			else if(request.responseText == "pwNotEqual")
				joinMsg.innerHTML = "password와 password 확인란이 일치하지 않습니다.";
			else if(request.responseText == "emailEmpty")
				joinMsg.innerHTML = "email을 입력해주세요";
			else if(request.responseText == "existingUser")
				joinMsg.innerHTML = "이미 존재하는 id입니다.";			
				 
			if(request.responseText == "joinOK")
			{			
				alert("회원 가입이 완료되었습니다.");
				joinCloseFunc();
			}
			joinSubmit.disabled = false;		
		}
	}
	else
	{
		joinSubmit.disabled = true;		
		joinMsg.innerHTML = "처리중입니다...";
	}
}

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
				<div id="joinFormWrapper">	
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
					<form method="POST" action="login.do">						
						<div id="idpw">
							<input id="userId" name="userId" type="text"/><br/>
							<input id="password" name="password" type="password"/>
						</div>
						<input id="login" type="image" src="${root}/image/mainpage/login.png"/>						
					</form>	
					<div id="loginHelp">
						<input id="joinOpen" type="button" value="회원가입"/>
						<a href = "${root}/notimplemented.jsp"> ID/PW찾기</a><br/>
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
		<a href="logout.do">로그아웃(임시)</a>		
		</div>			
	</div>
</body>
</html>