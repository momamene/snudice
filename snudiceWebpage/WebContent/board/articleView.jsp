<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="stylesheet" type="text/css" href="${root}/css/commonStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/menuStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>

<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/header.js"></script>
<script type="text/javascript" src="${root}/javascript/menuScript.js"></script> 
<script type="text/javascript">		
var root = "${root}";
window.onload = init;

function init()
{
	initHeader();
	initMenu();
	
	//댓글 쓰기 버튼
	var replySubmitButton = document.getElementById("replySubmitButton");
	if(replySubmitButton!=null)
		replySubmitButton.onclick = replySubmit;
	// 글 수정 버튼
	var articleDelButton = document.getElementById("articleDeleteButton");
	if(articleDelButton!=null)
		articleDelButton.onclick = function() { show_confirm('정말 지울꺼에요?',articleDeleteFunc);	};
}

function focusToReply()
{
	var replyWriteText = document.getElementById("replyWriteText");
	replyWriteText.focus();
}

//---------------event handler---------------
//글을 지운다.
var articleDeleteFunc = function() 
{	
	var url = "${root}/board/articleDelete.ajax";	
	var method = "POST";
	var param = "articleIndex="+encodeURIComponent("${param.articleIndex}");
	param += "&boardName="+encodeURIComponent("${param.boardName}");
	var callback = function()
	{
		window.location = "${root}/board/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}";	
	}
	var async = false;
	
	sendRequest(url,method,param,callback,async);	
}

//댓글을 쓴다
function replySubmit()
{	
	var writeTextTextarea = document.getElementById("replyWriteText");
	var writeText = writeTextTextarea.value;

	writeTextTextarea.value = "";
	
	var url = "${root}/board/replyWrite.ajax";	
	var method = "POST";
	var param = "articleIndex="+encodeURIComponent("${param.articleIndex}");
	param += "&replyText="+encodeURIComponent(writeText);
	param += "&boardName="+encodeURIComponent("${param.boardName}");
	var callback = replyComplete;
	var async = false;
	
	sendRequest(url,method,param,callback,async);
}

function replyComplete()
{
	if(request.readyState == 4) //작업이 완료되었을 때
	{
		if(request.status == 200)
		{
			window.location = "${root}/board/articleView.do?boardName=${param.boardName}&articleIndex=${param.articleIndex}&currPage=${param.currPage}&replySubmit=yes";
		}
	}
}

</script>

<title>글 보기</title>
</head>
<body>
	<div class="bodyWrapper">
		<%@ include file="/reuseModule/headerModule.jsp"%>
				
    	<div class="container">
    		<%@ include file="/reuseModule/menuModule.jsp"%>
    		
    		<div class="left"></div>
    		
    		<div class="center">          	
            	<table>
            		<tr id="articleTitleDateWrapper">
            			<td class="articleTitleContent">
            				<span>${articleInfo.title}</span>
            			</td>
            			<td class="articleDateTime">
                			<span>${articleInfo.dateTime}</span>
                		</td>
                	</tr>
                	<tr>
                		<td class="articleNickName" colspan="2">
                			${articleInfo.nickname}
                		</td>
                	</tr>
                	<tr>
                		<td id="articleTextContentView" class="articleTextContent" colspan="2">
            				${articleInfo.text}
            			</td>
            		</tr>
            	</table> 
            	
				<div id="reply">
					<div id="replyHead">
						댓글 ${replyCount}   
					</div>
					<div id="replyBackground">
						<div id="replyContainer">
						<c:forEach var="reply" items="${replyList}" varStatus="status">			
							<div class="replyInfo">
								<span>[${status.count}] ${reply.nickname}</span>
								<span id="replyDateTime">${reply.dateTime}</span>
							</div>								
							<div class="replyContent">${reply.replyText}</div>				
							<hr/>
						</c:forEach>
						</div>
						
						<c:if test="${canComment == true}">
							<div id="replyWrite">
								한번 단 댓글은 수정,삭제가 불가능 합니다. 쓰기 전에 한번 더 생각해 주세요.<br/>					
								<textarea id="replyWriteText"></textarea>
								<input id="replySubmitButton" type="image" value="댓글 쓰기" src="${root}/image/board/replyWrite.png"/>
							</div>
						</c:if>			
						</div>
					</div>
				
				<div id="articleButtonWrapper">
	            	<a href="${root}/board/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}">
	            		<img src="${root}/image/board/toFirstPage.png"/>
	            	</a>
	            	
	            	<!-- 글 수정 버튼 : admin도 남의 글을 수정할 수는 없음 -->
					<c:if test="${myArticle==true && canWrite==true}">						
						<a id="boardModify" href="${root}/board/articleModify.do?boardName=${param.boardName}&articleIndex=${articleInfo.articleIndex}&currPage=${param.currPage}">
							<img src="${root}/image/board/articleModify.png"/>
						</a>
					</c:if>
					
					<!--  글 삭제 버튼 : 본인과 admin 이 삭제 가능 -->
					<c:if test="${myArticle==true || canAdmin==true}">					
						<input id="articleDeleteButton" type="image" src="${root}/image/board/articleDelete.png" />
					</c:if>							
					
					<!-- 글쓰기 버튼 -->
					<c:if test="${canWrite == true}">
						<a id="boardWrite" href="${root}/board/articleWriteForm.do?boardName=${param.boardName}&currPage=${param.currPage}">
							<img src="${root}/image/board/articleWrite.png"/>
						</a>
					</c:if>
				</div>
					 	         		
        	</div>
			
        	<div class="right"></div>
		</div>	
			
		<%@ include file="/reuseModule/footerModule.jsp"%>
		
		<!-- 댓글을 썼다면 자신이 쓴 댓글을 볼 수 있게 focus를 댓글 쓰는 폼에 맞춘다 -->
		<c:if test="${param.replySubmit == 'yes' }">
			<script type="text/javascript">
				focusToReply();
			</script>
		</c:if>
	</div>
</body>
</html>