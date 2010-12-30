<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<title>관리자 페이지</title>
</head>
<body>
	<a href="${root}/admin">어드민민</a><br/>
	<a href="${root}/logout.do">로그아웃</a>
	
	<div class="boardList">
		<c:forEach var="board" items="${boardList}">
			<a href="${root}/articleList.do?boardName=${board.boardName}&currPage=0">${board.aliasName}</a><br/>
		</c:forEach>
	</div>	
</body>
</html>