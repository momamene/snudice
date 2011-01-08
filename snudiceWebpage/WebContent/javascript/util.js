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
	try //IE7+,Chrome,Fireforx,Opera,Safari 
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
			try //IE6,5
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

//요청을 보낸다.
function sendRequest(url,method,param,callback,async)
{
	var request = createRequest();
	if(request==null)
	{
		alert("AJAX 요청 객체를 만들 수 없습니다.");
		return;
	}	
	
	request.open(method,url,async);
	request.onreadystatechange = callback;
	if(method.toLowerCase()=="post")
		request.setRequestHeader("Content-type","application/x-www-form-urlencoded");	
	request.send(param);
}

//요청이 완료되면 현재 페이지를 새로고침 한다.
function refresh()
{
	if(request.readyState == 4) //작업이 완료되었을 때
	{
		if(request.status == 200)
		{
			location.reload(); //페이지 새로고침
		}
	}	
}

//element를 만든다.
function createElement(tagName,id,className)
{
	if(tagName==null )
		return;
	
	var element = document.createElement(tagName);		
	
	if(id!=null)
		element.id = id;
	
	if(className!=null)
		element.className = className;
	
	return element;
}

//엔터키를 치면 callback function이 실행되게 한다.
function enterKeyExec(elementId,callback)
{
	var element = document.getElementById(elementId);
	element.onkeydown = function()
	{
		var keynum;
		if(window.event) //IE			
			keynum = event.keyCode;		
		else if(event.which) //Firefox, Chorme, ETC
			keynum = event.which;		
		
		if(keynum==13) //엔터키를 친 경우
			callback();
	}
}