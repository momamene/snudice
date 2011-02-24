<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon"/>
<link rel="stylesheet" type="text/css" href="${root}/css/boardStyle.css"/>
<jsp:include page="/javascript/header.jsp"/>

<title>글 쓰기</title>
</head>
<body>    
	<div class="bodyWrapper">
		<jsp:include page="/reuseModule/headerModule.jsp"/>
		
		<div class="container">
			<div class="left"></div>
			
			<div class="center">
				<form method = "post" action="${root}/board/articleWrite.do">
					<input type="hidden" name="boardName" value="${param.boardName}"/>
					<input type="hidden" name="currPage" value="${param.currPage}"/>
					
					<% /* dong : 전에 항목들 없앰 글쓴이 이런것들..*/%>
					
					<table class="articleWriteModifyTable">

			    		<tr>
							<td class="articleTitleLabel">제목</td>
			    			<td class="articleTitleContent" colspan="3">
			    				<input class="noBorder" type = "text" name = "title">
			    			</td>
			    		</tr>			    	
			    		<tr>
			    			<td class="articleTextContent" colspan="4">			    			    			
			    				<textarea name = "content"></textarea>
			    			</td>			    			
			    		</tr>
						<tr>
							<td class="articleButtonContent" colspan = "3">
								<input class="articleWriteWrapper" type="image" src="${root}/image/board/articleWrite.png" />
								<a id="articleListWrapper" href="${root}/board/articleList.do?boardName=${param.boardName}&currPage=${param.currPage}">
								<img src="${root}/image/board/toFirstPage.png"/>
								</a>
							</td>
			    		</tr>
			    	</table>
				</form>
			</div>
			
			<div class="right"></div>
		</div>
		
		<jsp:include page="/reuseModule/footerModule.jsp"/>
	</div>
</body>
</html>
