#pragma once

#include <mysql.h>
#include "network.h"

#define DB_HOST "211.169.219.93" // �¿������� db�ּ�
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "prjn1267650600228229401496703205376"
#define DB_NAME "snudice"

#define USER_SELECT "SELECT `password` FROM `user` \
WHERE userId = '%s';" //"

#define FRIEND_INSERT "INSERT INTO `friend` \
VALUES ('%s','%s');" //"

#define FRIEND_SELECT_OR "SELECT * FROM `friend` \
WHERE `userId` = '%s' OR `friendId` = '%s';" //"

#define FRIEND_SELECT_AND "SELECT * FROM `friend` \
WHERE `userId` = '%s' AND `friendId` = '%s';" //"

// �� ������ ���� friend_delete(a,b) (b,a) �̷��� �ι� �ҷ��� �Ѵ�.
#define FRIEND_DELETE "DELETE FROM `friend` \
WHERE `userId` = '%s' AND `friendId` = '%s';" //"
  

#define BLOCK_INSERT "INSERT INTO `block` \
VALUES ('%s','%s');" //"

#define BLOCK_SELECT_OR "SELECT * FROM `block` \
WHERE `userId` = '%s' OR `blockId` = '%s';" //"

#define BLOCK_SELECT_AND "SELECT * FROM `block` \
WHERE `userId` = '%s' AND `blockId` = '%s';" //"

// �� ������ ���� block_delete(a,b) (b,a) �̷��� �ι� �ҷ��� �Ѵ�.
#define BLOCK_DELETE "DELETE FROM `block` \
WHERE `userId` = '%s' AND `blockId` = '%s';" //"

//������ ���� �ʴ´�.
#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test`\
(`index`,  `szID` , `szPW`) \
VALUES (\
NULL , '%s', '%s'\
);" //"

class gMysql {
public:
	static gMysql	*GetIF();
private:
	MYSQL m_conn;
	MYSQL *m_connection;

public:
	// mysql�� �õ��ϴ� �Լ�
	void init();

	// �� �Լ� get�� ��ü�Լ�
	// ������ userId�� �޾Ƽ� password�� �޴´�.
	// ��ȿ���� ���� ����̿��� ��� null�� return.
	char* passwordGet(char* userId);

	USER*		get(char* userId);
	
	void put(char* id,char* pw);	//���ô��� ����. ������ ������ ����.

	// friendPutOne�� ģ�� �� ���� �Է� �޴� �Լ��̴�.
	void friendPutOne(char* userId, char* friendId);

	// friendGet�� �ڽ��� ģ������ �迭�� return�ϴ� �Լ��̴�.
	// ���� ģ���� ������ null�� return�ȴ�.
	char* friendGet(char* userId);

	// friendDeleteOne�� �ڽ��� ģ�� �Ѹ��� �����ϴ� �Լ��̴�.
	// ���� ���� Ȥ�� �����Ϸ��� ģ���� �������� ������, false����,
	// �׷��� �ʴٰ� �� �����Ͽ����� true ���� return�Ѵ�.
	bool friendDeleteOne(char* userId, char* friendId);


	// blockPutOne�� ���� �� ��� �� ���� �Է� �޴� �Լ��̴�.
	void blockPutOne(char* userId,char* blockId);

	// blockGet�� �ڽ��� ������ ������� �迭�� return�ϴ� �Լ��̴�.
	// ���� ģ���� ������ null�� return�ȴ�.
	char* blockGet(char* userId);

	// blockDeleteOne�� �ڽ��� ������ ��� �Ѹ��� �����ϴ� �Լ��̴�.
	// ���� ���� Ȥ�� �����Ϸ��� ������ �������� ������, false����,
	// �׷��� �ʴٰ� �� �����Ͽ����� true ���� return�Ѵ�.
	bool blockDeleteOne(char* userId,char* blockId);

	void release();

	bool isFriendOneExisted(char* userId, char* friendId);
	bool isBlockOneExisted(char* userId, char* blockId);
};