<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript">
var articleDeleteFunc = function() 
{	
	window.location = "${root}/board/articleDelete.do?boardName=${param.boardName}&articleIndex=${articleInfo.articleIndex}&currPage=${param.currPage}";
}

window.onload = init;

function init()
{
	//event handler 를 추가한다.
	//댓글 쓰기 버튼
	var replySubmitButton = document.getElementById("replySubmitButton");
	replySubmitButton.onclick = replySubmit;
	// 글 수정 버튼
	var articleDelButton = document.getElementById("articleDeleteButton");
	if(articleDelButton==null) //글 수정 버튼이 없는 경우 (자기 글이 아닌 경우)
		return;
	articleDelButton.onclick = function() { show_confirm('정말 지울꺼에요?',articleDeleteFunc);	}	
}


function replySubmit()
{	
	var writeTextTextarea = document.getElementById("replyWriteText");
	var writeText = writeTextTextarea.value;

	writeTextTextarea.value = "";
	
	var url = "${root}/board/replyWrite.ajax";	
	var method = "POST";
	var param = "articleIndex=${param.articleIndex}&replyText="+writeText;
	var callback = refresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);
}

</script>

<title>${sessionScope.boardName}게시판</title>
</head>
<body>
	<div class="wrapper">
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
 
	<a href="${root}/board/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}">목록으로</a>
	<c:choose>
		<c:when test="${myArticle==true}">						
			<a id="boardModify" href="${root}/board/articleModify.do?boardName=${param.boardName}&articleIndex=${articleInfo.articleIndex}&currPage=${param.currPage}">수정</a>
			<input id="articleDeleteButton" type="button" value="삭제" />		
		</c:when>													
	</c:choose>	
	<a id="boardWrite" href="${root}/board/articleWriteForm.do?boardName=${param.boardName}&currPage=${param.currPage}">새글쓰기</a>	 
	</div>		
	
	<div id="footer">
		<div id="reply">
			<div id="replyHead">총 댓글 수 : ${replyCount}</div>
			<hr/>
			
			<div id="replyContainer">
			<c:forEach var="reply" items="${replyList}" varStatus="status">			
				<div class="replyInfo">
					[${status.count}] id : ${reply.userId}, ${reply.dateTime}
				</div>									
				<div class="replyContent">${reply.replyText}</div>				
				<hr/>
			</c:forEach>
			</div>
			
			<div id="replyWrite">
				<textarea id="replyWriteText"></textarea>
				<input id="replySubmitButton" type="button" value="댓글 쓰기">
			</div>			
		</div>
	</div>
	</div>
</body>
</html>