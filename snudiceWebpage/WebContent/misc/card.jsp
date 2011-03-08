<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="icon" href="${root}/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="${root}/favicon.ico" type="image/x-icon">  
<link rel="stylesheet" type="text/css" href="${root}/css/commonStyle.css">
<link rel="stylesheet" type="text/css" href="${root}/css/loginModuleStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/menuStyle.css"/>
<link rel="stylesheet" type="text/css" href="${root}/css/gameIntro.css">
<script type="text/javascript" src="${root}/javascript/json2.js"></script>
<script type="text/javascript" src="${root}/javascript/util.js"></script>
<script type="text/javascript" src="${root}/javascript/md5.js"></script> 
<script type="text/javascript" src="${root}/javascript/header.js"></script>
<script type="text/javascript" src="${root}/javascript/menuScript.js"></script> 
<script type="text/javascript" src="${root}/javascript/login.js"></script> 
<script type="text/javascript"> 
var root = "${root}";
window.onload = function() {
	initHeader();
	initMenu();
	initLogin();
};

var _userId = "${userId}";
var _role = "${role}";
</script>
<title>카드</title>
</head>
<body>
	<div class="bodyWrapper">		
		<%@ include file="/reuseModule/headerModule.jsp"%>
		
		<div class="container">		
			<%@ include file="/reuseModule/menuModule.jsp"%>					
					
			<div class="leftCenterRightWrapper">				
				<div class="left">
					<%@ include file="/reuseModule/loginModule.jsp"%>
				
					<div id="mainLeftBottom">						
									
					</div>					
				</div>
				
				<div class="center">
					<div class="boardFrameTop"></div>
						<div class="boardFrameBody">
							<div id="cardBody">
								<div id="cardInfor">
								<span>카드는 카드 타일에 도착하면 한장씩 얻게 되며, 네 장 이상은 가지고 있을 수 없습니다.</span>
								<span>다양한 카드를 적재적소에 활용해 게임에서 승리하세요!</span>
								</div>
								<div id="cardStudy">
									<span>학습력 카드</span>
									<hr/>
									<span>
										<img src="${root}/image/misc/item00.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item01.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item02.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item03.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item04.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item05.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item06.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item07.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item08.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item09.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item10.png"/>
									</span>
								</div>
								<div id="cardStamina">
									<span>체력 카드</span>
									<hr/>
									<span>
										<img src="${root}/image/misc/item11.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item12.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item13.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item14.png"/>
									</span>
								</div>
								<div id="cardClass">
									<span>수업 카드</span>
									<hr/>
									<span>
										<img src="${root}/image/misc/item16.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item17.png"/>
									</span>
								</div>
								<div id="cardMove">
									<span>이동 카드</span>
									<hr/>
									<span>
										<img src="${root}/image/misc/item15.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item18.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item19.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item20.png"/>
									</span>
								</div>
								<div id="cardLove">
									<span>연애 카드</span>
									<hr/>
									<span>
										<img src="${root}/image/misc/item21.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item22.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item23.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item24.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item25.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item26.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item27.png"/>
									</span>
									<span>
										<img src="${root}/image/misc/item28.png"/>
									</span>
								</div>
							</div>
					</div>
					<div class="boardFrameBottom"></div>
				</div>
				
				<div class="right"></div>
				<div class="dummy"></div>
			</div>
			
			<div class="containerBottom"></div>
		</div>
		
		<%@ include file="/reuseModule/footerModule.jsp"%>
		
	</div>
</body>
</html>