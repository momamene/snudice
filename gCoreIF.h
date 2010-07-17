//------------------------------------------------------------------------------------
//	gCoreIF Class
//
//	2010. 07. 16	CoderK
//
//	Core의 인터페이스 역할(가상클래스)을 한다. 모든 Core는 얘를 상속시켜서 한다.
//	상속 후에 이들 함수를 모두 구현해야 함.
//------------------------------------------------------------------------------------
#pragma once

class gCoreIF  
{
	virtual bool SetUp() = 0;			// virtual type func() = 0;  means 순수가상함수.
	virtual void MainLoop() = 0;
	virtual void Draw() = 0;

	//about mouse
	virtual void OnLButtonDown() = 0;
	virtual void OnLButtonUp() = 0;
	virtual void OnMouseMove() = 0;
	virtual void OnRButtonDown() = 0;
};
