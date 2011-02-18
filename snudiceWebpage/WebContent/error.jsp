<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/errorPage.css">
<script type="text/javascript">
<jsp:include page="/javascript/header.jsp"/>
</script>  

<title>에러!!!</title>

</head>
<body>
	<div class="bodyWrapper centerOfAllWidth">
		<jsp:include page="/reuseModule/headerModule.jsp"/>
		
		<div class="container">
			<div class="left"></div>
			
			<div class="center">
				<br/><br/><br/><br/>				
				에러입니다!!!
			</div>
			
			<div class="right"></div>
		</div>
		
		<jsp:include page="/reuseModule/footerModule.jsp"/>
	</div>
</body>
</html>