//------------------------------------------------------------------------------------
//	gUtil Class
//
//	2010. 07. 18	CoderK
//
//	�̰����� �����ִ� �Լ���. no ��ü ����
//	text ����� �� ������ �����Ҷ� begin, ������ end
//------------------------------------------------------------------------------------
#pragma once

class gUtil  
{
public:
	static void BeginText();
	static void Text(int x, int y, char *str, int lineterm = 20);	//lineterm -> ����ĥ�� �󸶳� ����������
	static void EndText();
};

