<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
  
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<script type="text/javascript">

window.onload = init;

function init()
{
	var headerImage = document.getElementById("headerImage");
	headerImage.onclick = function() { window.location = "${root}/first.do"};
}

</script> 

<title>${boardAliasName}</title>
</head>
<body>
	<div class="bodyWrapper">
		<div class="header">
			<div id="headerImage"></div>
		</div>		
		
		<div class="container">	
			<div class="left"></div>
					
			<div class = "center">
				<table id = "articleListMain">
					<tr id="articleListHeader">
						<td>번호</td>
						<td>제목</td>
						<td>글쓴이</td>
						<td>날짜</td>
						<td>조회수</td>
					</tr>
					
					<c:forEach var="article" items="${articleList}" varStatus="status">	
						<tr class="article">
							<td>${article.articleIndex}</td>
							<td>								
								<a href="${root}/board/articleView.do?boardName=${param.boardName}&amp;articleIndex=${article.articleIndex}&amp;currPage=${param.currPage}">															
									<span>${article.title}</span> 
									<c:if test="${replyCountList[status.index]>0}">
										<span> (${replyCountList[status.index]})</span>
									</c:if>
								</a>
							</td>
							<td>${article.userId}</td>
							<td>${article.dateTime}</td> 
							<td>${article.readCount}</td>		
						</tr>
					</c:forEach>					 
				</table>
			</div>
			
			<table id="articleListBottom">
				<tr>
					<td> 
						<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goPrev=true">
							<img src="${root}/image/board/prev.png" alt="앞페이지"/>
						</a> 
					</td>
					<c:forEach var="pageNumber" items="${pageList}">
						<td>					
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
					<td> 
						<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goNext=true">
							<img src="${root}/image/board/next.png" alt="뒷페이지"/>
						</a> 
					</td>
				</tr>			
			
				<tr>
					<td colspan="3">현재 페이지 : ${param.currPage}	</td>					
				</tr>  					
				<tr>
					<td>
						<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=0">처음목록</a>
					</td>
					<td>
						<a href="${root}/board/articleWriteForm.do?boardName=${param.boardName}&amp;currPage=${param.currPage}">글쓰기</a>
					</td>
					<td>
						<a href="${root}/logout.do">로그아웃</a>
					</td>					
				</tr>			
			</table>
			
			<div class="right"></div>
		</div>		
	
		<div class="footer">
		<hr/>PrjN
		</div>	
	</div>	
</body>
</html>