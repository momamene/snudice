<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript">
var articleDeleteFunc = function() 
{
	window.location = "${root}/articleDelete.do?boardName=${param.boardName}&articleIndex=${articleInfo.articleIndex}&currPage=${param.currPage}";
}
</script>

<title>${sessionScope.boardName}게시판</title>
</head>
<body>
	<div class="boardRead">
    <div class="originalContent">
        <div class="readHeader">
            <div class="titleAndUser">
            	<div class="title">
                	<h1>${articleInfo.title }</h1>
                </div>   
                <div class="user">
                    <h2>${articleInfo.userId }</h2>
                </div>        
                <div class="clear"></div> 
            </div>
 
            <div class="dateAndCount"> 
                <div class="date" title="등록일">
                    <strong>${articleInfo.dateTime }</strong>
                </div>
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
 
	<a href="${root}/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}">처음목록</a>
	<c:choose>
		<c:when test="${myArticle==true}">			
			<a id="boardModify" href="${root}/articleModify.do?boardName=${param.boardName}&articleIndex=${articleInfo.articleIndex}&currPage=${param.currPage}">수정</a>
			<input type="button" onclick="show_confirm('정말 지울꺼에요?',articleDeleteFunc)" value="삭제" />		
		</c:when>													
	</c:choose>	
	<a id="boardWrite" href="${root}/articleWriteForm.do?boardName=${param.boardName}&currPage=${param.currPage}">새글쓰기</a> 
	</div>		
</body>
</html>