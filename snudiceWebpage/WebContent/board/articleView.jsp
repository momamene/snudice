<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="/godwar/css/boardStyle.css"/>
<title>${sessionScope.boardName}게시판</title>
</head>
<body>	
<jsp:useBean id="articleInfo" class="beans.ArticleInfo" scope="request"/>


<div class="boardRead">
    <div class="originalContent">
        <div class="readHeader">
            <div class="titleAndUser">
 
                <div class="title">
                    <h1>${articleInfo.title }</h1>
                </div>   
                <div class="user">
                    <h1>${articleInfo.userId }</h1>
                </div>        
                <div class="clear"></div>
 
            </div>
 
            <div class="dateAndCount">
 
                <div class="date" title="등록일">
                    <strong>${articleInfo.dateTime }</strong>               </div>
				
 
             
                <div class="clear"></div>
            </div>
 
            <div class="clear"></div>
        </div>
 
        <div class="clear"></div>
 
        
        <div class="readBody">
            <div class="contentBody">
 
                           ${articleInfo.text }

            </div>
                        </div>
                                    </div>
 
<a href="/godwar/articleList.do?currPage = ${sessionScope.currPage}">처음목록</a>
	<a id="boardModify" href="/godwar/articleModify.do?&articleIndex=${articleInfo.articleIndex}">수정</a>
	<a id="boardWrite" href="/godwar/board/articleWrite.jsp?boardName=${sessionScope.boardName}">글쓰기</a>

 
</div>

		
</body>
</html>