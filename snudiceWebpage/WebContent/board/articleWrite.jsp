<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="/snudiceWebpage/css/boardStyle.css"/>
<title>BBS</title>
</head>
<body>      
	<br/>
  	<center>
   	<b>
    	<font size = "4">게시판 글쓰기</font>
	</b>
	</center>
 	<br/>

	<form action="/snudiceWebpage/articleWrite.do?boardName=${param.boardName}&currPage=${param.currPage}" method = "post"><!--  post로 정보를 보내야 하나? -->
	<center>
		<table width = "650" border = "1" cellpadding = "2" cellspacing = "0" bordercolor = "#000000">
			<tr>
				<td align = "center" width = "80">ID</td>
    			<td width = "*">
    				${userId}
					<br/>
				</td>
    		</tr>
    		<tr>
				<td align = "center" width = "80">게시판이름</td>
    			<td width = "*">
    				${param.boardName}
					<br/>
				</td>
    		</tr>
    		<tr>
     			<td align = "center" width = "80">제목</td>
     			<td width = "*">
     				<input type = "text" name = "title" size = "60">
     			</td>
    		</tr>
    		<tr>
    			<td align = "center" width = "80">내용</td>
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
	</center>

	</form>
</body>
</html>
