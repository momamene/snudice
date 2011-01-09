<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" type="text/css" href="${root}/css/loginPageStyle.css">
<script type="text/javascript" src="${root}/javascript/util.js"></script> 
<script type="text/javascript">

window.onload = init;

function init()
{
	window.onresize = function()
	{
		windowAutoResize(1024);
	}
	
	var headerImage = document.getElementById("gameIntroHeaderImage");
	headerImage.onclick = function() { window.location = "${root}"};
	
	var introCenterIframe = document.getElementById("introCenterIframe");
	
	var synopsys = document.getElementById("synopsys");
	var gameManual = document.getElementById("gameManual");
	var charIntro = document.getElementById("charIntro");

	synopsys.onclick = function()
	{
		introCenterIframe.src = "${root}/misc/synopsis.do";
	}
	
	gameManual.onclick = function()
	{
		introCenterIframe.src = "${root}/misc/gameManual.do";
	}
	
	charIntro.onclick = function()
	{
		introCenterIframe.src = "${root}/misc/charIntro.do";
	}
}
</script> 
<title>게임소개</title>
</head>
<body>
	<div class="bodyWrapper">
		<div class="header">
			<div id="gameIntroHeaderImage"></div>
		</div>
		
		<div class="container">			
			<div id="introLeft" class="left">
				<span>게임소개</span><br/>
				<span id="synopsys">시놉시스</span><br/>
				<span id="gameManual">게임방법</span><br/>
				<span id="charIntro">캐릭터소개</span><br/>												
			</div>
			
			<div id="introCenter" class="center">
				<iframe id="introCenterIframe" src ="${root}/misc/synopsis.do"  marginheight="0" marginwidth="0" frameborder="0">
	  				<p>브라우져가 iframe을 지원하지 않아 내용을 볼 수 없습니다.</p>
				</iframe>		
			</div>
			
			<div class="right"></div>
		</div>
		
		<div class="footer centerAlign">
			<hr class="lightColor"/>${footerMsg}
		</div>
	</div>
</body>
</html>