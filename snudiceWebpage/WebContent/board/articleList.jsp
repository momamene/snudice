<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
  
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>

<jsp:include page="/javascript/header.jsp"/>

<title>${boardAliasName}</title>
</head>
<body>
	<div class="bodyWrapper">
		<jsp:include page="/reuseModule/headerModule.jsp"/>	
		
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
						<c:set var="tdClassName" value="normal"/>
						<c:if test="${status.first == true}">
							<c:set var="tdClassName" value="first"/>							
						</c:if>
						<c:if test="${status.last == true}">
							<c:set var="tdClassName" value="last"/>							
						</c:if>
						<c:if test="${ (status.first == true) && (status.last ==true)}">
							<c:set var="tdClassName" value="firstLast"/>							
						</c:if>	
						
						<tr class="article">
							<td class="${tdClassName}">${article.articleIndex}</td>
							<td class="${tdClassName}">								
								<c:set var="articleReadLink" value="#"/>								
								<c:if test="${canRead == true}">
									<c:set var="articleReadLink" value="${root}/board/articleView.do?boardName=${param.boardName}&amp;articleIndex=${article.articleIndex}&amp;currPage=${param.currPage}"/>
								</c:if>														
													
								<a href="${articleReadLink}">															
									<span>${article.title}</span> 
									<c:if test="${replyCountList[status.index]>0}">
										<span> (${replyCountList[status.index]})</span>
									</c:if>
								</a>
							</td>
							<td class="${tdClassName}">${article.nickname}</td>
							<td class="${tdClassName}">${article.dateTime}</td> 
							<td class="${tdClassName}">${article.readCount}</td>		
						</tr>
					</c:forEach>					 
				</table>
				
				<c:url var="titleKeywordEncoded" value="${titleKeyword}"/>			
				<table id="articleListBottom">
					<tr>
						<td class="prevNextPage"> 					
							<c:choose>
								<c:when test="${not empty search}">
									<c:set var="nextUrl" value="${root}/board/articleSearch.do?titleKeyword=${titleKeywordEncoded}&boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goPrev=true"/>								
								</c:when>
								<c:otherwise>
									<c:set var="nextUrl" value="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goPrev=true"/>
								</c:otherwise>
							</c:choose>	
							<a href="${nextUrl}">
								<img src="${root}/image/board/prev.png" alt="앞페이지"/>
							</a> 
						</td>			
							
						<td class="pageNumber">
						<c:forEach var="pageNumber" items="${pageList}">						
							<c:choose>
								<c:when test="${not empty search}">
									<c:set var="nextUrl" value="${root}/board/articleSearch.do?titleKeyword=${titleKeywordEncoded}&boardName=${param.boardName}&amp;currPage=${pageNumber}"/>								
								</c:when>
								<c:otherwise>
									<c:set var="nextUrl" value="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${pageNumber}"/>
								</c:otherwise>
							</c:choose>
										
							<c:choose>
								<c:when test="${pageNumber==param.currPage}">
									<c:set var="formattedPageNumber" value="(${pageNumber})"/>
								</c:when>
								<c:otherwise>
									<c:set var="formattedPageNumber" value="${pageNumber}"/>
								</c:otherwise>
							</c:choose>
							<a href=${nextUrl}>${formattedPageNumber }</a>					
						</c:forEach>
						</td>
						<td class="prevNextPage"> 
							<c:choose>
								<c:when test="${not empty search}">
									<c:set var="nextUrl" value="${root}/board/articleSearch.do?titleKeyword=${titleKeywordEncoded}&boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goNext=true"/>								
								</c:when>
								<c:otherwise>
									<c:set var="nextUrl" value="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=${param.currPage}&amp;goNext=true"/>
								</c:otherwise>
							</c:choose>	
							<a href="${nextUrl}">
								<img src="${root}/image/board/next.png" alt="뒷페이지"/>
							</a> 					
						</td>
					</tr>			
				
					<tr>
						<td colspan="3">현재 페이지 : ${param.currPage}	</td>					
					</tr>  					
					<tr>
						<td id="firstList">
							<a href="${root}/board/articleList.do?boardName=${param.boardName}&amp;currPage=0">처음목록</a>
						</td>
						<td id="search">
							<form method="get" action="${root}/board/articleSearch.do">
								<span>검색 : </span><input name="titleKeyword" type="text"/>
								<input type="submit" value="검색"/>
								<input type="hidden" name="boardName" value="${param.boardName}"/>
								<input type="hidden" name="currPage" value="0"/>							
							</form>
						</td>
						<td id="articleWrite">
							<c:if test="${canWrite == true}">
								<a href="${root}/board/articleWriteForm.do?boardName=${param.boardName}&amp;currPage=${param.currPage}">글쓰기</a>
							</c:if>
						</td>										
					</tr>			
				</table>
			</div>
			
			<div class="right"></div>
		</div>		
	
		<jsp:include page="/reuseModule/footerModule.jsp"/>
	</div>	
</body>
</html>