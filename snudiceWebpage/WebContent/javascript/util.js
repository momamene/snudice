//Ȯ��â(yes,no ����)�� ����. yes ���ý� callbackFunc�� ����ȴ�.
function show_confirm(msg,callbackFunc)
{
	var r=confirm(msg);
	if (r==true)
	{
		alert("You pressed OK!");
		callbackFunc();
	}	
}


