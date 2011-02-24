//header image 클릭시 메인 페이지로 이동한다.
function initHeader()
{
	window.onresize = function()
	{
		windowAutoResize(1024);
	};
	
	var headerImage = document.getElementsByClassName("headerImage");
	headerImage[0].onclick = function() { window.location = root ; };	
}