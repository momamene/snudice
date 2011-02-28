<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix ="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%@ include file="/reuseModule/joinAndIdpwFindModule.jsp"%>

<!-- 회원 정보 수정 form -->
<div id="infoModifyForm" class="display_none">					
	<div id="infoModifyTitle">정보수정</div>	
		<table id="infoModifyFormTable">
			<tr>
				<td class="label">기존pw</td>
				<td><input id="pastPw" type="password" name="pastPw"/></td>									
			</tr>
			<tr>
				<td class="label">
					새로운pw<br/>
					<span class="noticeMsg">(입력하지 않을 시 변경하지 않음)</span>
				</td>
				<td><input id="newPw" type="password" name="newPw"/></td>									
			</tr>
			<tr>
				<td class="label">새로운pw확인</td>
				<td><input id="newPwConfirm" type="password" name="newPwConfirm"/></td>									
			</tr>
			<tr>
				<td class="label">email</td>
				<td><input id="newEmail" type="text" name="newEmail"/></td>									
			</tr>
			<tr>
				<td class="label">자기소개</td>
				<td><input id="newComment" type="text" name="newComment"/></td>									
			</tr>
		</table>
	<div id="infoModifyMsg" class="msg"></div>
	<div id="infoModifyButtonWrapper">
		<span id="infoModifyExec" class="button">정보수정</span>
		<span id="infoModifyClose" class="button">닫기</span>
	</div>																						
</div>

<!-- 로그인 Form -->
<c:choose>
	<c:when test="${not empty userId}">
		<c:set var="loginFormWrapperClass" value="invisible"/>	
		<c:set var="mainLeftTopClass" value="loggined"/>
	</c:when>
	<c:otherwise>
		<c:set var="loginFormWrapperClass" value="visible"/>	
		<c:set var="mainLeftTopClass" value="logouted"/>
	</c:otherwise>
</c:choose>

<div id="mainLeftTop" class="${mainLeftTopClass}">						
	<div id="loginFormTitle" class="${loginFormWrapperClass}">	
		&nbsp;&nbsp;회원로그인					
		<div id="guestLogin"></div> 
	</div>		
	
	<div id="loginFormWrapper" class="${loginFormWrapperClass}">									
		<div id="idpw">
			ID<input id="userId" name="userId" type="text"/><br/>
			PW<input id="password" name="password" type="password"/>
		</div>					
		<div id="loginButton" class="mouseOut"></div>
								
		<div id="loginHelp">
			<hr/>												
			<a id="joinOpen" href="#">빠른 회원가입</a>							
			<a id="findIdPw" href="#">ID/PW찾기</a>
		</div>						
	</div>
	<c:choose>
		<c:when test="${not empty userId}">
			<c:set var="loginMsgClass" value="loggined"/>
		</c:when>	
		<c:otherwise>
			<c:set var="loginMsgClass" value="logouted"/>
		</c:otherwise>											
	</c:choose>	
	
	<div id="loginMsg" class="${loginMsgClass} msg">
		<c:choose>
			<c:when test="${not empty userId}">
				${userId} 님 로그인 하셨습니다.
			</c:when>												
		</c:choose>	
	</div>
	<c:choose>
		<c:when test="${not empty userId}">
			<c:set var="logginedButtonWrapperClass" value="visible"/>		
		</c:when>
		<c:otherwise>
			<c:set var="logginedButtonWrapperClass" value="invisible"/>		
		</c:otherwise>
	</c:choose>		
	<div id="logginedButtonWrapper" class="${logginedButtonWrapperClass}">
		<div id="logoutButton"></div>
		<c:choose>
			<c:when test="${role=='guest'}">
				<c:set var="infoModifyButtonClass" value="unavailable"/>
			</c:when>
			<c:otherwise>
				<c:set var="infoModifyButtonClass" value="available"/>
			</c:otherwise>
		</c:choose>
		<div id="infoModifyButton" class="${infoModifyButtonClass}"></div>
	</div>																	
</div>