#pragma once

#include <mysql.h>
#include "network.h"

//#define DB_HOST "211.169.219.93" // �¿������� db�ּ�
#define DB_HOST "localhost" // �¿������� db�ּ�
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

#define USER_NICKNAME_SELECT "SELECT `nickname` FROM `user` \
WHERE `userId` = '%s';" 

#define USER_COMMENT_SELECT "SELECT `comment` FROM `user` \
WHERE `nickname` = '%s';" 


#define USER_ROLE_SELECT "SELECT `role` FROM `user_roles` \
WHERE `userId` = '%s';" 

#define USER_IDbyNICKNAME_SELECT "SELECT `userId` FROM `user` \
WHERE `nickname` = '%s';" 

#define BLOCK_INSERT "INSERT INTO `block` \
VALUES ('%s','%s');" 

#define BLOCK_SELECT_OR "SELECT * FROM `block` \
WHERE `userId` = '%s' OR `blockId` = '%s';" 

#define BLOCK_SELECT_AND "SELECT * FROM `block` \
WHERE `userId` = '%s' AND `blockId` = '%s';" 

// �� ������ ���� block_delete(a,b) (b,a) �̷��� �ι� �ҷ��� �Ѵ�.
#define BLOCK_DELETE "DELETE FROM `block` \
WHERE `userId` = '%s' AND `blockId` = '%s';" 

//������ ���� �ʴ´�.
#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test`\
(`index`,  `szID` , `szPW`) \
VALUES (\
NULL , '%s', '%s'\
);" //"

/*	���ô��� ����
#define USER_WIN_COUNT "UPDATE `userscore` SET `winCount` = `winCount` + 1   \
WHERE `userId` = '%s' ;"

#define USER_LOSE_COUNT "UPDATE `userscore` SET `loseCount` = `loseCount` + 1   \
WHERE `userId` = '%s' ;"

#define USER_WINCOUNT_SELECT "SELECT `winCount` FROM `userscore` \
WHERE `userId` = '%s';" 

#define USER_LOSECOUNT_SELECT "SELECT `loseCount` FROM `userscore` \
WHERE `userId` = '%s';" 
*/


#define USERSCORE_DROP_COUNT "UPDATE `userscore` SET `dropCount` = `dropCount` + 1   \
WHERE `nickname` = '%s' ;"

#define USERSCORE_GAMEPLAY_COUNT "UPDATE `userscore` SET `gameplayCount` = `gameplayCount` + 1   \
WHERE `nickname` = '%s' ;"

#define USERSCORE_MAJOR_COUNT "UPDATE `userscore` SET `%sCount` = `%sCount` + 1   \
WHERE `nickname` = '%s' ;"


#define USERSCORE_GRADEMAX_UPDATE "UPDATE `userscore` SET `gradeMax` = '%f'   \
WHERE `nickname` = '%s' ;"

#define USERSCORE_GRADESUM_UPDATE "UPDATE `userscore` SET `gradeSum` = `gradeSum` + '%f'   \
WHERE `nickname` = '%s' ;"

#define USERSCORE_GRADEAVR_UPDATE "UPDATE `userscore` SET `gradeAvr` = '%f'   \
WHERE `nickname` = '%s' ;"

#define USERSCORE_SCORE_UPDATE "UPDATE `userscore` SET `score` = '%d'   \
WHERE `nickname` = '%s' ;"


#define USERSCORE_DROP_SELECT "SELECT `dropCount` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define USERSCORE_GAMEPLAY_SELECT "SELECT `gameplayCount` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define USERSCORE_MAJOR_SELECT "SELECT `'%s'Count` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define USERSCORE_GRADEMAX_SELECT "SELECT `gradeMax` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define USERSCORE_GRADESUM_SELECT "SELECT `gradeSum` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define USERSCORE_GRADEAVR_SELECT "SELECT `gradeAvr` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define USERSCORE_SCORE_SELECT "SELECT `score` FROM `userscore`	\
WHERE `nickname` = '%s' ;"

#define RANK_GRADEMAX_SELECT	"SELECT `gradeMaxRank` FROM `rank`	\
WHERE `nickname` = '%s' ;"


class gMysql {
public:
	static gMysql	*GetIF();
private:
	MYSQL m_conn;
	MYSQL *m_connection;
	CRITICAL_SECTION dbLock;

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

//	void scoreCountAdd(char* userId , bool val);	//	val = 1 : winCount�߰� , val = 0 : loseCount�߰� 
//	int	 getScoreCount(char* userId , bool val);				//	val = 1 : get winCount , val = 0 : get loseCount 

	void dropCountAdd(char* userId);
	int	 getDropCount(char* userId);

	void gameplayCountAdd(char* userId);
	int	 getGameplayCount(char* userId);

	void majorCountAdd(char* userId , char *mayor);
	int	 getMajorCount(char* userId , char *mayor);

	void	gradeMaxUpdate(char* userId , double grade);
	double	getGradeMax(char* userId);

	void	gradeSumUpdate(char* userId , double grade);
	double	getGradeSum(char* userId);

	void	gradeAvrUpdate(char* userId , double grade);
	double	getGradeAvr(char* userId);
	
	void	scoreUpdate(char* userId , int endTurn , int maxUser , int myRank);
	int		getScore(char* userId);

	char* nicknameGet(char* userId);
	char* commentGet(char* userId);
	
	int		getRank(char* userId);

	char* roleGet( char* userId );
	char* IDbyNicknameGet( char* nickname );
	void release();

	bool isFriendOneExisted(char* userId, char* friendId);
	bool isBlockOneExisted(char* userId, char* blockId);
};