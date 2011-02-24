//header image 클릭시 메인 페이지로 이동한다.
function initHeader()
{
	window.onresize = function()
	{
		windowAutoResize(1024);
	};		
	
	var headerImage = document.getElementById("headerImage");	
	headerImage.onclick = function() { window.location = root ; };	
}