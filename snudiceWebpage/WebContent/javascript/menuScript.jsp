<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

//메뉴관련 초기화
function initMenu() {	
	var menu1 = document.getElementById("menu1");
	menu1.onmouseover = function() {		
		var menu1DropDown = document.getElementById("menu1DropDown");
		menu1DropDown.className = "menuDropDownWrapper visible"; 
	};
	menu1.onmouseout = function() {		
		var menu1DropDown = document.getElementById("menu1DropDown");
		menu1DropDown.className = "menuDropDownWrapper invisible"; 
	};
	
	var menu2 = document.getElementById("menu2");
	menu2.onmouseover = function() {
		var menu2DropDown = document.getElementById("menu2DropDown");
		menu2DropDown.className = "menuDropDownWrapper visible"; 
	};
	menu2.onmouseout = function() {
		var menu2DropDown = document.getElementById("menu2DropDown");
		menu2DropDown.className = "menuDropDownWrapper invisible"; 
	};
	
	var menu3 = document.getElementById("menu3");
	menu3.onmouseover = function() {
		var menu3DropDown = document.getElementById("menu3DropDown");
		menu3DropDown.className = "menuDropDownWrapper visible"; 
	};
	menu3.onmouseout = function() {
		var menu3DropDown = document.getElementById("menu3DropDown");
		menu3DropDown.className = "menuDropDownWrapper invisible"; 
	};
	
	var menu4 = document.getElementById("menu4");
	menu4.onmouseover = function() {
		var menu4DropDown = document.getElementById("menu4DropDown");
		menu4DropDown.className = "menuDropDownWrapper visible"; 
	};
	menu4.onmouseout = function() {
		var menu4DropDown = document.getElementById("menu4DropDown");
		menu4DropDown.className = "menuDropDownWrapper invisible"; 
	};
	
	var menu5 = document.getElementById("menu5");
	menu5.onmouseover = function() {
		var menu5DropDown = document.getElementById("menu5DropDown");
		menu5DropDown.className = "menuDropDownWrapper visible"; 
	};
	menu5.onmouseout = function() {
		var menu5DropDown = document.getElementById("menu5DropDown");
		menu5DropDown.className = "menuDropDownWrapper invisible"; 
	};	
}