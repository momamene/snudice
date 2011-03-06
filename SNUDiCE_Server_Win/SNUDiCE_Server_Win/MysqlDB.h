#pragma once

#include <mysql.h>
#include "network.h"

//#define DB_HOST "211.169.219.93" // 승엽이형의 db주소
#define DB_HOST "localhost" // 승엽이형의 db주소
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

// 이 쿼리문 등은 friend_delete(a,b) (b,a) 이렇게 두번 불러야 한당.
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

// 이 쿼리문 등은 block_delete(a,b) (b,a) 이렇게 두번 불러야 한당.
#define BLOCK_DELETE "DELETE FROM `block` \
WHERE `userId` = '%s' AND `blockId` = '%s';" 

//실제로 쓰지 않는다.
#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test`\
(`index`,  `szID` , `szPW`) \
VALUES (\
NULL , '%s', '%s'\
);" //"

/*	고대시대의 유물
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
	// mysql을 시동하는 함수
	void init();

	// 옛 함수 get의 대체함수
	// 하지만 userId를 받아서 password를 받는다.
	// 유효하지 않은 명령이였을 경우 null을 return.
	char* passwordGet(char* userId);

	USER*		get(char* userId);
	
	void put(char* id,char* pw);	//구시대의 잔재. 실제로 쓰이지 않음.

	// friendPutOne은 친구 한 명을 입력 받는 함수이다.
	void friendPutOne(char* userId, char* friendId);

	// friendGet은 자신의 친구들을 배열로 return하는 함수이다.
	// 만약 친구가 없으면 null이 return된다.
	char* friendGet(char* userId);

	// friendDeleteOne은 자신의 친구 한명을 제거하는 함수이다.
	// 만약 유저 혹은 제거하려는 친구가 존재하지 않으면, false값을,
	// 그렇지 않다고 잘 제거하였으면 true 값을 return한다.
	bool friendDeleteOne(char* userId, char* friendId);


	// blockPutOne은 차단 할 사람 한 명을 입력 받는 함수이다.
	void blockPutOne(char* userId,char* blockId);

	// blockGet은 자신이 차단한 사람들을 배열로 return하는 함수이다.
	// 만약 친구가 없으면 null이 return된다.
	char* blockGet(char* userId);

	// blockDeleteOne은 자신의 차단한 사람 한명을 제거하는 함수이다.
	// 만약 유저 혹은 차단하려는 유저가 존재하지 않으면, false값을,
	// 그렇지 않다고 잘 제거하였으면 true 값을 return한다.
	bool blockDeleteOne(char* userId,char* blockId);

//	void scoreCountAdd(char* userId , bool val);	//	val = 1 : winCount추가 , val = 0 : loseCount추가 
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