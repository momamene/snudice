<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript">

function boardDelete(boardName) 
{	
	var url = "admin/boardDelete.ajax";		
	var method = "POST";
	var param = "boardName="+boardName;
	var callback = refresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);
}

</script>
<title>관리자 페이지</title>
</head>
<body>
	<a href="${root}/admin">어드민민</a><br/>
	<a href="${root}/logout.do">로그아웃</a>
	
	<div class="boardList">
		<c:forEach var="board" items="${boardList}">			
			<a href="${root}/articleList.do?boardName=${board.boardName}&currPage=0">${board.aliasName}</a>
			<input onclick="show_confirm('정말 지울꺼에요?', function() {boardDelete('${board.boardName}')});" type="button" value="게시판 삭제"/><br/>		
		</c:forEach>
	</div>
	TODO : 게시판 생성하기 (각 role에 따른 권한도 설정)<br/>
	TODO : 권한에 따른 게시판 접근 설정(공지게시판은 어드민 또는 메니져만 쓸수있다)<br/>	
</body>
</html>