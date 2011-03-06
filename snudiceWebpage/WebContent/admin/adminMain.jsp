<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon"/>

<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript">

window.onload = init;

function init()
{
	var rankRefresh = document.getElementById("rankRefresh");
	rankRefresh.onclick = rankRefreshFunc;
	
	var createBoard = document.getElementById("createBoard");
	createBoard.onclick = createBoardFunc;
}

function boardDelete(boardName) 
{	
	var url = "admin/deleteBoard.ajax";		
	var method = "POST";
	var param = "boardName="+boardName;
	var callback = refresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);
}

function rankRefreshFunc()
{
	var url = "admin/rankRefresh.ajax";		
	var method = "GET";
	var param = null;
	var callback = refresh;
	var async = true;
	
	sendRequest(url,method,param,callback,async);
}

function createBoardFunc()
{
	var createBoardName = document.getElementById("createBoardName");
	var createBoardAliasName = document.getElementById("createBoardAliasName");
	
	var url = "admin/createBoard.ajax";		
	url += "?boardName="+encodeURIComponent(createBoardName.value);
	url += "&aliasName="+encodeURIComponent(createBoardAliasName.value);
	var method = "GET";
	var param = null;	
	var callback = refresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);
}

</script>
<title>관리자 페이지</title>
</head>
<body>	
	<a href="${root}/logout.do">로그아웃</a><br/>	
	
	<input id="rankRefresh" type="button" value="rank Refresh"/><br/>
	
	<c:forEach var="board" items="${boardList}">			
		<a href="${root}/board/articleList.do?boardName=${board.boardName}&currPage=0">${board.aliasName}</a>
		<input onclick="show_confirm('정말 지울꺼에요?', function() {boardDelete('${board.boardName}')});" type="button" value="게시판 삭제"/><br/>		
	</c:forEach>
	<br/>
	
	이름 : <input id="createBoardName" type="text"/>
	별명 : <input id="createBoardAliasName" type="text"/>
	<input id="createBoard" type="button" value="게시판 생성"/><br/>
			
</body>
</html>