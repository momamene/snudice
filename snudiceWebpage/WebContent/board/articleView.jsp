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

window.onload = init;

function init()
{
	//event handler 를 추가한다.
	var articleDelButton = document.getElementById("articleDeleteButton");
	articleDelButton.onclick = function() { show_confirm('정말 지울꺼에요?',articleDeleteFunc);	}
	var replySubmitButton = document.getElementById("replySubmitButton");
	replySubmitButton.onclick = replySubmit;

	ajaxtest();
}

function ajaxtest()
{
	var request = createRequest();
	if(request==null)
	{
		alert("AJAX 요청 객체를 만들 수 없습니다.");
		return;
	}
	
	var url = "testAjax.ajax";	
	var params = "arg0=haha&arg1=hoho";
	
	request.open("POST",url,true);
	request.onreadystatechange = testcallback;
	request.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	request.send(params);
}

function testcallback()
{
	alert('test callback');
}

function replySubmit()
{	
	var writeTextTextarea = document.getElementById("replyWriteText");
	var writeText = writeTextTextarea.value;
	var replyContainer = document.getElementById("replyContainer");
	var replyAuthor = document.createElement("div");
	
	replyAuthor.className = "replyAuthor";	
	replyAuthor.innerHTML = "아 여기 글쓴이 id가 들어가야 되는데";	
	var replyContent = document.createElement("div");
	replyContent.className = "replyContent";
	replyContent.innerHTML = writeText;
	var hr = document.createElement("hr");
	
	replyContainer.appendChild(hr);	
	replyContainer.appendChild(replyAuthor);
	replyContainer.appendChild(replyContent);

	writeTextTextarea.value = "";	
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
 
	<a href="${root}/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}">목록으로</a>
	<c:choose>
		<c:when test="${myArticle==true}">						
			<a id="boardModify" href="${root}/articleModify.do?boardName=${param.boardName}&articleIndex=${articleInfo.articleIndex}&currPage=${param.currPage}">수정</a>
			<input id="articleDeleteButton" type="button" value="삭제" />		
		</c:when>													
	</c:choose>	
	<a id="boardWrite" href="${root}/articleWriteForm.do?boardName=${param.boardName}&currPage=${param.currPage}">새글쓰기</a>	 
	</div>		
	
	<div id="footer">
		<div id="reply">
			<div id="replyHead">reply Head - 총 리플 수 등</div>
			<hr/>
			<div id="replyContainer">				
				<div class="replyAuthor">글쓴이id</div>				
				<div class="replyContent">리플 내용</div>				
			</div>
			<hr/>
			<div id="replyWrite">
				<textarea id="replyWriteText"></textarea>
				<input id="replySubmitButton" type="button" value="댓글 쓰기">
			</div>			
		</div>
	</div>
</body>
</html>