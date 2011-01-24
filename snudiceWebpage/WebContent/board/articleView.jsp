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
<script type="text/javascript">
window.onload = init;

function init()
{
	window.onresize = function()
	{
		windowAutoResize(1024);
	}
	
	//event handler 를 추가한다.
	//header image 클릭시
	var headerImage = document.getElementById("articleViewHeaderImage");
	headerImage.onclick = function() { window.location = "${root}"; }
	//댓글 쓰기 버튼
	var replySubmitButton = document.getElementById("replySubmitButton");
	replySubmitButton.onclick = replySubmit;
	// 글 수정 버튼
	var articleDelButton = document.getElementById("articleDeleteButton");
	if(articleDelButton==null) //글 수정 버튼이 없는 경우 (자기 글이 아닌 경우)
		return;
	articleDelButton.onclick = function() { show_confirm('정말 지울꺼에요?',articleDeleteFunc);	}
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
		<div class="header">
			<div id="articleViewHeaderImage" class="headerImage"></div>
		</div>
				
    	<div class="container">
    		<div class="left"></div>
    		
    		<div class="center centerAlign">          	
            	<span>${articleInfo.title}</span>   
            	<br/>
                <span>${articleInfo.userId}</span>
                <br/> 
                <span>${articleInfo.dateTime}</span>            	
                <br/>
            	<span>${articleInfo.text}</span>		
            	<br/>
            	
            	<a href="${root}/board/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}">목록으로</a>
            	
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
				
				<div id="reply">
					<div id="replyHead">
						총 댓글 수 : ${replyCount}
					</div>
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
					
					<c:if test="${canComment == true}">
						<div id="replyWrite">
							한번 단 댓글은 수정,삭제가 불가능 합니다. 쓰기 전에 한번 더 생각해 주세요.<br/>					
							<textarea id="replyWriteText"></textarea>
							<input id="replySubmitButton" type="button" value="댓글 쓰기">
						</div>
					</c:if>			
				</div>	 	         		
        	</div>
			
        	<div class="right"></div>
		</div>	
			
		<div class="footer centerAlign">
			<hr class="lightColor"/>${footerMsg}
		</div>
		
		<!-- 댓글을 썼다면 자신이 쓴 댓글을 볼 수 있게 focus를 댓글 쓰는 폼에 맞춘다 -->
		<c:if test="${param.replySubmit == 'yes' }">
			<script type="text/javascript">
				focusToReply();
			</script>
		</c:if>
	</div>
</body>
</html>