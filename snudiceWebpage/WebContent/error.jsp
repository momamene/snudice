<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript">
	
window.onload = init;

function init()
{
	var errorHeaderImage = document.getElementById("errorHeaderImage");
	errorHeaderImage.onclick = function()
	{
		window.location = "${root}";
	}
}
	
</script>

<title>에러!!!</title>

</head>
<body>
	<div class="bodyWrapper centerOfAllWidth">
		<div class="header">
			<div id="errorHeaderImage"></div>
		</div>
		
		<div class="container">
			<div class="left"></div>
			
			<div class="center centerAlign">
			에러입니다!!!
			</div>
			
			<div class="right"></div>
		</div>
		
		<div class="footer centerAlign">
			<hr/>PrjN
		</div>
	</div>
</body>
</html>