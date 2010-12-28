//확인 창을 띄우고, yes를 선택하면 callbackFunc 를 실행한다.
function show_confirm(msg,callbackFunc)
{
	var r=confirm(msg);
	if (r==true)
	{		
		callbackFunc();
	}	
}


