//확인창(yes,no 선택)을 띄운다. yes 선택시 callbackFunc가 실행된다.
function show_confirm(msg,callbackFunc)
{
	var r=confirm(msg);
	if (r==true)
	{
		alert("You pressed OK!");
		callbackFunc();
	}	
}


