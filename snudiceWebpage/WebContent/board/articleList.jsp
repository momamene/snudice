<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
  
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<title>${param.boardName} 게시판</title>
</head>
<body>
	<div class="bodyWrapper">
		<div class="header">
			<div id="headerImage"></div>
		</div>		
		
		<div class="container">
			<div class = "boardTop"></div>
			<div class = "boardMiddle">
				<table class="boardListTop">
					<tr>
						<td class="articleNumber">번호</td>
						<td class="articleTitle">제목</td>
						<td class="articleWriter">글쓴이</td>
						<td class="articleDateTime">날짜</td>
						<td class="articleReadCount">조회수</td>
					</tr>
					
					<c:forEach var="article" items="${articleList}" varStatus="status">	
						<tr>
							<td class="articleNumber">${article.articleIndex}</td>
							<td class="articleTitle">								
								<a href="${root}/board/articleView.do?boardName=${param.boardName}&amp;articleIndex=${article.articleIndex}&amp;currPage=${param.currPage}">															
									<span>${article.title}</span> 
									<c:if test="${replyCountList[status.index]>0}">
										<span> (${replyCountList[status.index]})</span>
									</c:if>
								</a>
							</td>
							<td class="articleWriter">${article.userId}</td>
							<td class="articleDateTime">${article.dateTime}</td> 
							<td class="articleReadCount">${article.readCount}</td>		
						</tr>
					</c:forEach>					 
				</table>
			</div>
		</div>		
		
		<div class = "boardBottom">
			<table class="boardListBottom">
				<tr>
					<td class="pageNumber"> 
						<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goPrev=true">prev</a> 
					</td>
					<c:forEach var="pageNumber" items="${pageList}">
						<td class="pageNumber">					
							<c:choose>
								<c:when test="${pageNumber==param.currPage}">
									<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${pageNumber}"> (${param.currPage})</a>
								</c:when>
								<c:otherwise>
									<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${pageNumber}"> ${pageNumber}</a>
								</c:otherwise>
							</c:choose>
						</td>
					</c:forEach>
					<td class="pageNumber"> 
						<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goNext=true">next</a> 
					</td>
				</tr>
			</table>
		</div>			
	</div>		
	
	<div class="footer">
		<span>현재 페이지 : ${param.currPage}</span>  		
		<br/>
		<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=0">처음목록</a>
		<a id="boardWrite" href="${root}/board/articleWriteForm.do?boardName=${param.boardName}&amp;currPage=${param.currPage}">글쓰기</a>
		<a href="${root}/logout.do">로그아웃</a>
	</div>	
</body>
</html>