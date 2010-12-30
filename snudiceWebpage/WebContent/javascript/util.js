//확인 창을 띄우고, yes를 선택하면 callbackFunc 를 실행한다.
function show_confirm(msg,callbackFunc)
{
	var r=confirm(msg);
	if (r==true)
	{		
		callbackFunc();
	}	
}

//요청 객체를 만든다. 모든 브라우져를 고려한다.
function createRequest()
{
	try 
	{
		request = new XMLHttpRequest();
	}
	catch(tryMS)
	{
		try
		{
			request = new ActiveXObject("Msxml2.XMLHTTP");
		}
		catch(otherMS)
		{
			try
			{
				request = new ActiveXObject("Microsoft.XMLHTTP");
			}
			catch(failed)
			{
				request = null;
			}			
		}
	}	
	return request;
}