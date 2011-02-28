<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/commonStyle.css">
<link rel="stylesheet" type="text/css" href="${root}/css/errorPage.css">
<script type="text/javascript" src="${root}/javascript/header.js"></script>
<script type="text/javascript">
var root = "${root}";
window.onload = function() {
	initHeader();
}
</script>

<title>에러!!!</title>

</head>
<body>
	<div class="bodyWrapper">
		<%@ include file="/reuseModule/headerModule.jsp"%>
		
		<div class="container">
			<div class="left"></div>
			
			<div class="center">
				<br/><br/><br/><br/>				
				에러입니다!!!
			</div>
			
			<div class="right"></div>
		</div>
		
		<%@ include file="/reuseModule/footerModule.jsp"%>
	</div>
</body>
</html>