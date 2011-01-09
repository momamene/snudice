window.onload = initLogin;
var root = "/snudiceWebpage";

//event handler 추가	
function initLogin()
{	
	window.onresize = function()
	{
		windowAutoResize(1024);
	}	
	
	//가입창 열기 버튼	
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.onclick = joinOpenFunc;	
	//가입창  버튼
	var joinCloseButton = document.getElementById("joinClose");
	joinCloseButton.onclick = joinCloseFunc;
	//가입하기 버튼
	var joinSubmit = document.getElementById("joinSubmit");
	joinSubmit.onclick = joinSubmitFunc;
	//로그인 버튼
	var loginButton = document.getElementById("loginButton");
	loginButton.onclick = loginFunc;
	loginButton.onmouseover = mousOverFunc;
	loginButton.onmouseout = mouseOutFunc;
	
	//패스워드 창에서 엔터 치면 로그인시킴
	enterKeyExec("password",loginFunc);

	//로그아웃 버튼
	var logoutWrapper = document.getElementById("logoutWrapper");
	logoutWrapper.onclick = function() { window.location = "logout.do"; }
	
	//손님 로그인 버튼
	var guestLogin = document.getElementById("guestLogin");
	guestLogin.onclick = guestLoginFunc;
}

////////////////////ajax 요청을 하는 event handler/////////////////////
//회원 가입 창을 연다
function joinOpenFunc()
{	
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.disabled = true;
	
	var joinFormWrapper = document.getElementById("joinFormWrapper");		
	joinFormWrapper.className = "display_block";	
}

//회원 가입 창을 닫는다
function joinCloseFunc()
{			
	var joinOpen = document.getElementById("joinOpen");
	joinOpen.disabled = false;
	
	var joinSubmit = document.getElementById("joinSubmit");
	joinSubmit.disabled = false;
	
	var joinFormWrapper = document.getElementById("joinFormWrapper");	
	var joinId = document.getElementById("joinId");
	var joinPw = document.getElementById("joinPw");
	var joinPwConfirm = document.getElementById("joinPwConfirm");
	var joinEmail = document.getElementById("joinEmail");
	var joinMsg = document.getElementById("joinMsg");

	joinId.value = "";
	joinPw.value = "";
	joinPwConfirm.value = "";
	joinEmail.value = "";
	joinMsg.innerHTML = "";
	
	joinFormWrapper.className = "display_none";
}

//회원 가입 요청을 보낸다
function joinSubmitFunc()
{	
	var joinId = document.getElementById("joinId");
	var joinPw = document.getElementById("joinPw");
	var joinPwConfirm = document.getElementById("joinPwConfirm");
	var joinEmail = document.getElementById("joinEmail");
	var joinSubmit = document.getElementById("joinSubmit");	

	var joinMsg = document.getElementById("joinMsg");
	
	//validation
	if(joinId.value=="")
	{
		joinMsg.innerHTML = "id를 입력해주세요.";
		joinId.focus();
		return;
	}
	if(joinPw.value=="")
	{
		joinMsg.innerHTML = "password를 입력해주세요.";
		joinPw.focus();
		return;
	}
	if(joinPwConfirm.value=="")
	{
		joinMsg.innerHTML = "password 확인란에 입력해 주세요.";
		joinPwConfirm.focus();
		return;
	}
	if(joinPw.value!=joinPwConfirm.value)
	{
		joinMsg.innerHTML = "password와 password 확인란이 일치하지 않습니다.";
		joinPwConfirm.focus();
		joinPwConfirm.select();
		return;
	}
	if(joinEmail.value=="")
	{
		joinMsg.innerHTML = "email을 입력해주세요";
		joinEmail.focus();
		return;
	}

	joinMsg.innerHTML = "가입처리중입니다...";
	joinSubmit.disabled = true;	
	
	var url = root+"/join.ajax";	
	var method = "POST";
	var param = "joinId="+encodeURIComponent(joinId.value);
	param += "&joinPw="+encodeURIComponent(joinPw.value);	
	param += "&joinEmail="+encodeURIComponent(joinEmail.value);
	var callback = joinFormRefresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);		
}

//로그인 요청을 보낸다.
function loginFunc()
{
	var userId = document.getElementById("userId");
	var password = document.getElementById("password");	

	var loginMsg = document.getElementById("loginMsg");	

	//validation
	if(userId.value=="")
	{
		loginMsg.innerHTML = "id를 입력해 주세요";
		userId.focus();
		return;
	}
	if(password.value=="")
	{
		loginMsg.innerHTML = "password를 입력해 주세요";
		password.focus();
		return;
	}	

	loginMsg.innerHTML = "로그인 중입니다..";
	
	var url = root+"/login.ajax";	
	var method = "POST";
	var param = "userId="+encodeURIComponent(userId.value);
	param += "&password="+encodeURIComponent(password.value);	
	var callback = loginFormRefresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);	
}

//손님으로 로그인한다.
function guestLoginFunc()
{
	var userId = document.getElementById("userId");	
	userId.value = "guest";
	var loginMsg = document.getElementById("loginMsg");	
	loginMsg.innerHTML = "로그인 중입니다..";
	
	var url = root+"/login.ajax";	
	var method = "POST";
	var param = "userId=guest";
	param += "&password=guest";	
	var callback = loginFormRefresh;
	var async = false;
	
	sendRequest(url,method,param,callback,async);	
}

////////////////////이미지 변화 event handler/////////////////////
//마우스를 올려놓는 경우
function mousOverFunc()
{
	this.className = "mouseOver";	
}

//마우스를 떼는 경우
function mouseOutFunc()
{
	this.className = "mouseOut";
}

////////////////////callback function/////////////////////
function joinFormRefresh()
{		
	var joinId = document.getElementById("joinId");
	var joinPw = document.getElementById("joinPw");
	var joinEmail = document.getElementById("joinEmail");
	var joinSubmit = document.getElementById("joinSubmit");	
	var joinMsg = document.getElementById("joinMsg");

	if(request.readyState == 4)
	{		
		joinSubmit.disabled = false;
		
		if(request.status == 200)
		{				
			if(request.responseText == "idContainSpace")
			{
				joinMsg.innerHTML = "id는 공백문자를 포함할 수 없습니다.";
				joinId.focus();
				joinId.select();
			}				
			else if(request.responseText == "idTooLong")
			{
				joinMsg.innerHTML = "id가 너무 깁니다.";
				joinId.focus();
				joinId.select();
			}
			else if(request.responseText == "pwContainSpace")
			{
				joinMsg.innerHTML = "password는 공백문자를 포함할 수 없습니다.";
				joinPw.focus();
				joinPw.select();
			}	
			else if(request.responseText == "pwTooLong")
			{
				joinMsg.innerHTML = "password가 너무 깁니다.";
				joinPw.focus();
				joinPw.select();
			}
			else if(request.responseText == "emailContainSpace")
			{
				joinMsg.innerHTML = "email은 공백문자를 포함할 수 없습니다.";
				joinEmail.focus();
				joinEmail.select();
			}	
			else if(request.responseText == "emailTooLong")
			{
				joinMsg.innerHTML = "email이 너무 깁니다.";
				joinEmail.focus();
				joinEmail.select();
			}
			else if(request.responseText == "invalidId")
			{
				joinMsg.innerHTML = "id 는 영어 소문자,숫자만 허용됩니다."
				joinId.focus();
				joinId.select();
			}
			else if(request.responseText == "existingUser")
			{
				joinMsg.innerHTML = "이미 존재하는 id입니다.";
				joinId.focus();
				joinId.select();
			}						
				 
			if(request.responseText == "joinOK")
			{			
				alert("회원 가입이 완료되었습니다.");
				joinCloseFunc();
			}
		}
	}	
}

function loginFormRefresh()
{	
	var userId = document.getElementById("userId");	
	var loginMsg = document.getElementById("loginMsg");	
	var logoutWrapper = document.getElementById("logoutWrapper");		
	
	if(request.readyState == 4)
	{		
		if(request.status == 200)
		{			
			if(request.responseText=="loginOK")
			{
				loginMsg.innerHTML = userId.value + " 님 로그인 하셨습니다.";
				var loginFormWrapper = document.getElementById("loginFormWrapper");
				var loginFormTitle = document.getElementById("loginFormTitle");
				
				loginMsg.className = "loggined";
				loginFormWrapper.className = "invisible";
				loginFormTitle.className = "invisible";
				logoutWrapper.className = "visible";				
			}
			else if(request.responseText=="loginFail")
			{				
				loginMsg.innerHTML = "로그인 실패!";
				userId.focus();
				userId.select();
			}
			else if(request.responseText=="alreadyLoggined")
			{
				loginMsg.innerHTML = "이미 로그인 되어있습니다.";
				logoutWrapper.className = "visible";
			}			
		}
	}	
}
