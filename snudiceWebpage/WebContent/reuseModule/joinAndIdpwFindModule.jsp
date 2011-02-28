<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!--  회원가입 Form -->					
<div id="joinFormWrapper" class="display_none">	
	<div id="joinTitle">회원가입</div>																
	<table id="joinFormTable">
		<tr>
			<td class="label">ID</td>
			<td><input id="joinId" type="text" name="id"/></td>
		</tr>
		<tr>
			<td class="label">PW</td>
			<td><input id="joinPw" type="password" name="pw"/></td>
		</tr>
		<tr>
			<td class="label">PW확인</td>
			<td><input id="joinPwConfirm" type="password" name="pwConfirm"/></td>
		</tr>
		<tr>
			<td class="label">email<br/>
				<span class="noticeMsg">(인증시 사용됨)</span>								
			</td>
			<td><input id="joinEmail" type="text" name="email"/></td>
		</tr>
		<tr>
			<td class="label">별명<br/>
				<span class="noticeMsg">(게임상에 보여짐)</span>
			</td>
			<td><input id="joinNickname" type="text" name="nickname"/></td>
		</tr>
		<tr>
			<td class="label">자기소개</td>
			<td><input id="joinComment" type="text" name="comment"/></td>
		</tr>
	</table>								

	<div id="joinMsg" class="msg"></div>
	<span id="joinSubmit" class="button">가입하기</span>					
	<span id="joinClose" class="button">닫기</span>						
</div>

<!-- 아이디,비번 찾기 Form -->
<div id="idpwFindForm" class="display_none">
	<div id="idpwFindTitle">id,pw 찾기</div>	
	<table id="idpwFindFormTable">
		<tr>
			<td class="label">email</td>
			<td><input id="idpwFindEmail" type="text" name="idpwFindEmail"/></td>
			<td><span id="idFind" class="button">id찾기</span></td>
		</tr>
		<tr>
			<td class="label">id</td>
			<td><input id="idpwFindId" type="text" name="idpwFindId"/></td>
			<td><span id="pwFind" class="button">pw찾기</span></td>
		</tr>
	</table>
	<div id="idpwFindMsg" class="msg"></div>										
	<div id="idpwFindClose" class="button">닫기</div>
</div>
