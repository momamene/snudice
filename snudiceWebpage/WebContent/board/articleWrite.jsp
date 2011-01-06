<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<script type="text/javascript">
window.onload = init;

function init()
{
	//event handler 를 추가한다.
	//header image 클릭시
	var headerImage = document.getElementById("articleWriteHeaderImage");
	headerImage.onclick = function() { window.location = "${root}/first.do"};
}
</script>
<title>글 쓰기</title>
</head>
<body>    
	<div class="bodyWrapper">
		<div class="header">
			<div id="articleWriteHeaderImage" class="headerImage"></div>
		</div>
		
		<div class="container">
			<div class="left"></div>
			
			<div class="center">
				<form action="${root}/board/articleWrite.do?boardName=${param.boardName}&currPage=${param.currPage}" method = "post"><!--  post로 정보를 보내야 하나? -->
					<table id="articleWriteTable">
						<tr>
							<td>ID</td>
			    			<td>${userId}</td>
			    		</tr>
			    		<tr>
							<td>게시판이름</td>
			    			<td>${param.boardName}</td>
			    		</tr>
			    		<tr>
			     			<td>제목</td>
			     			<td>
			     				<input type = "text" name = "title">
			     			</td>
			    		</tr>
			    		<tr>
			    			<td>내용</td>
			    			<td>    			
			    				<textarea name = "content" rows = "8" cols="60"></textarea>
			    			</td>
			    		</tr>
						<tr>
							<td colspan = "2">
								<input type = "submit" value = "글쓰기">
							</td>
			    		</tr>
			    	</table>
				</form>
			</div>
			
			<div class="right"></div>
		</div>
		
		<div class="footer centerAlign">
			<hr/>PrjN
		</div>
	</div>
</body>
</html>
