<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript">
window.onload = init;

function init()
{
	initHeader();
}

function initHeader()
{
	window.onresize = function()
	{
		windowAutoResize(1024);
	};
	
	var headerImage = document.getElementsByClassName("headerImage");
	headerImage[0].onclick = function() { window.location = "${root}"; };	
}
</script>