<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<form method="get" action="/godwar/board.do">
	<div class="boardSection">			
		<span>testboard로 바로가기</span>
		<input type="checkbox" name="boardName" value = "test" tabindex="1"><br/>
		<INPUT type="hidden" name="action" value="list">
		<INPUT type="hidden" name="page" value="0"> <!--  0base임 -->
		<input type="submit" value="gogo" tabindex="3">    		        
	</div>
</form>
</body>
</html>