#include "mysqlDB.h"
//#include "const.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#pragma comment(lib, "libmySQL.lib") 
#pragma comment(lib, "ws2_32.lib")   

static gMysql s_Mysql;

gMysql* gMysql::GetIF() 
{
	return &s_Mysql;
}

void gMysql::init() {
	InitializeCriticalSection(&dbLock);

	mysql_init(&m_conn);

	unsigned int maxtime = 4294967293;

	m_connection = mysql_real_connect(&m_conn,DB_HOST,
		DB_USER,DB_PASS,DB_NAME,DB_PORT,(char*)NULL,0);
	if(m_connection==NULL) {

		fprintf(stderr,"Mysql connection error : %s",mysql_error(&m_conn));
		return;
	}

	mysql_query(m_connection, "SET NAMES euckr");
}

void gMysql::release() {
	mysql_close(m_connection);
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void gMysql::put(char* id,char* pw) {
	EnterCriticalSection(&dbLock);	

	char query[255];
	int query_stat;

	if(get(id)!=NULL) {
		fprintf(stderr,"This ID %s is already existed\n",id);
		LeaveCriticalSection(&dbLock);
		return;
	}


	sprintf(query,SQL_INSERT_RECORD,id,pw);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return;
	}

	LeaveCriticalSection(&dbLock);
}


USER* gMysql::get(char* userId) {
	EnterCriticalSection(&dbLock);

	USER *user = new USER;
	char*	pass;
	strcpy(user->szID , userId);

	pass = passwordGet(userId);
	if(pass)
	{
		strcpy(user->szPW, pass);
		SAFE_DELETE_ARRAY(pass);
	}

	LeaveCriticalSection(&dbLock);
	return user;
}

char* gMysql::passwordGet(char* userId) {
	EnterCriticalSection(&dbLock);

	char* password = new char[33];
	char query[255];
	sprintf(query,USER_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		delete password;
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row != NULL) {
		strncpy(password,sql_row[0],33);
	}
	else {
		strcpy(password,"");
	}
	LeaveCriticalSection(&dbLock);
	return password;

}

void gMysql::friendPutOne(char* userId, char* friendId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	int query_stat;

	if(isFriendOneExisted(userId,friendId)) {
		fprintf(stderr,"Friend Connection %s - %s is already existed\n",userId,friendId);
		LeaveCriticalSection(&dbLock);
		return;
	}

	sprintf(query,FRIEND_INSERT,userId,friendId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return;
	}
	LeaveCriticalSection(&dbLock);
}

// �ʹ� �����̰� �� ���ư��� �� Ȯ���� �ȵ��.
// �� �� ���� �׽�Ʈ�� ��ĥ��
bool gMysql::isFriendOneExisted(char* userId, char* friendId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,FRIEND_SELECT_AND,userId,friendId);

	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return false;
	}

	MYSQL_RES* sql_resultA = mysql_store_result(m_connection);
	int count = mysql_num_rows(sql_resultA);
	if(count != 0) {
		LeaveCriticalSection(&dbLock);
		return true;
	}

	sprintf(query,FRIEND_SELECT_AND,friendId,userId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return false;
	}

	MYSQL_RES* sql_resultB = mysql_store_result(m_connection);
	count = mysql_num_rows(sql_resultB);
	if(count != 0) {
		LeaveCriticalSection(&dbLock);
		return true;
	}
	LeaveCriticalSection(&dbLock);
	return false;
}

// ������ ������ return �Ѵ�.
// �̰� �ɰ��� �����Ϸ���...
// �� �� ������ ������ delete ���ָ� ���� �� ����.
// "test1,test2,test3,test4"
char* gMysql::friendGet(char* userId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,FRIEND_SELECT_OR,userId,userId);

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* friendArr = new char [arrLength*17];
	strcpy(friendArr,"");

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL; // �ƹ��� ģ���� ������ 
	}

	for(int i = 0 ; i < arrLength ; i++) {

		MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
		if(sql_row == NULL) {
			fprintf(stderr,"friendGet() : null error");
		}
		else {
			if(strcmp(userId,sql_row[0])==0) {
				strcat(friendArr,sql_row[1]);
				if(i != arrLength -1) strcat(friendArr," ");
			}
			else if(strcmp(userId,sql_row[1])==0) {
				strcat(friendArr,sql_row[0]);
				if(i != arrLength -1) strcat(friendArr," ");
			}
			else {
				fprintf(stderr,"friendGet() : no userId error");
			}			
		}
	}	

	LeaveCriticalSection(&dbLock);
	return friendArr;
}
char* gMysql::nicknameGet(char* userId)
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USER_NICKNAME_SELECT,userId);

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* gotNickname = new char [arrLength*17];
	strcpy(gotNickname,"");

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row == NULL) {
		fprintf(stderr,"nicknameGet() : null error");
	}
	else {
		strcpy(gotNickname , sql_row[0]);
	}	

	LeaveCriticalSection(&dbLock);
	return gotNickname;
}

bool gMysql::friendDeleteOne(char* userId, char* friendId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,FRIEND_DELETE,userId,friendId);
	int query_statA = mysql_query(m_connection,query);

	sprintf(query,FRIEND_DELETE,friendId,userId);
	int query_statB = mysql_query(m_connection,query);

	if(query_statA != 0 && query_statB != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	LeaveCriticalSection(&dbLock);
	return true;
}
/* ���ô��� ����
void gMysql::scoreCountAdd(char* userId, bool val) {

	char query[255];
	if (val)	{
		sprintf(query,USER_WIN_COUNT,userId);
	}	else	{
		sprintf(query,USER_LOSE_COUNT,userId);
	}
	
	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
}
*/





//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void gMysql::blockPutOne(char* userId, char* blockId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	int query_stat;

	if(isBlockOneExisted(userId,blockId)) {
		fprintf(stderr,"Block Connection %s - %s is already existed\n",userId,blockId);
		LeaveCriticalSection(&dbLock);
		return;
	}

	sprintf(query,BLOCK_INSERT,userId,blockId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return;
	}

	LeaveCriticalSection(&dbLock);
}

// �ʹ� �����̰� �� ���ư��� �� Ȯ���� �ȵ��.
// �� �� ���� �׽�Ʈ�� ��ĥ��
bool gMysql::isBlockOneExisted(char* userId, char* blockId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,BLOCK_SELECT_AND,userId,blockId);

	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return false;
	}

	MYSQL_RES* sql_resultA = mysql_store_result(m_connection);
	int count = mysql_num_rows(sql_resultA);
	if(count != 0) {
		LeaveCriticalSection(&dbLock);
		return true;
	}

	sprintf(query,BLOCK_SELECT_AND,blockId,userId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return false;
	}

	MYSQL_RES* sql_resultB = mysql_store_result(m_connection);
	count = mysql_num_rows(sql_resultB);
	if(count != 0) {
		LeaveCriticalSection(&dbLock);
		return true;
	}
	LeaveCriticalSection(&dbLock);
	return false;
}

// ������ ������ return �Ѵ�.
// �̰� �ɰ��� �����Ϸ���...
// �� �� ������ ������ delete ���ָ� ���� �� ����.
// "test1,test2,test3,test4"
char* gMysql::blockGet(char* userId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,BLOCK_SELECT_OR,userId,userId);

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* blockArr = new char [arrLength*17];
	strcpy(blockArr,"");

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	for(int i = 0 ; i < arrLength ; i++) {

		MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
		if(sql_row == NULL) {
			fprintf(stderr,"blockGet() : null error");
		}
		else {
			if(strcmp(userId,sql_row[0])==0) {
				strcat(blockArr,sql_row[1]);
				if(i != arrLength -1) strcat(blockArr,",");
			}
			else if(strcmp(userId,sql_row[1])==0) {
				strcat(blockArr,sql_row[0]);
				if(i != arrLength -1) strcat(blockArr,",");
			}
			else {
				fprintf(stderr,"blockGet() : no userId error");
			}			
		}
	}	

	LeaveCriticalSection(&dbLock);
	return blockArr;
}

bool gMysql::blockDeleteOne(char* userId, char* blockId) {
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,BLOCK_DELETE,userId,blockId);
	int query_statA = mysql_query(m_connection,query);

	sprintf(query,BLOCK_DELETE,blockId,userId);
	int query_statB = mysql_query(m_connection,query);

	if(query_statA != 0 && query_statB != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}
	LeaveCriticalSection(&dbLock);
	return true;
}


/* ���ô��� ����
int gMysql::getScoreCount(char* userId , bool val) {

	int returnValue = -1;
	char query[255];
	if (val)
		sprintf(query,USER_WINCOUNT_SELECT,userId);
	else
		sprintf(query,USER_LOSECOUNT_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getScoreCount() : null error");
	}
	else {
		returnValue = atoi(sql_row[0]);
	}
	return returnValue;
}
*/

char* gMysql::roleGet( char* userId )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USER_ROLE_SELECT,userId);

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* gotRole = new char [arrLength*17];
	strcpy(gotRole,"");

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL;
	}
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row == NULL) {
		fprintf(stderr,"roleGet() : null error");
	}
	else {
		strcpy(gotRole , sql_row[0]);
	}

	LeaveCriticalSection(&dbLock);
	return gotRole;
}

char* gMysql::IDbyNicknameGet( char* nickname )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USER_IDbyNICKNAME_SELECT,nickname);

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* gotId = new char [arrLength*17];
	strcpy(gotId,"");

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL;
	}
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row == NULL) {
		fprintf(stderr,"nicknameGet() : null error");
	}
	else {
		strcpy(gotId , sql_row[0]);
	}	

	LeaveCriticalSection(&dbLock);
	return gotId;
}

void gMysql::dropCountAdd( char* userId )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USERSCORE_DROP_COUNT,userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

int gMysql::getDropCount( char* userId )
{
	EnterCriticalSection(&dbLock);

	int returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_DROP_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getDropCount() : null error");
	}
	else {
		returnValue = atoi(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}

void gMysql::gameplayCountAdd( char* userId )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USERSCORE_GAMEPLAY_COUNT,userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

int gMysql::getGameplayCount( char* userId )
{
	EnterCriticalSection(&dbLock);

	int returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_GAMEPLAY_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getGameplayCount() : null error");
	}
	else {
		returnValue = atoi(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}


void gMysql::majorCountAdd( char* userId , char *major )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USERSCORE_MAJOR_COUNT,major,major , userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

int gMysql::getMajorCount( char* userId , char *major )
{
	EnterCriticalSection(&dbLock);

	int returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_MAJOR_SELECT, major,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getMajorCount() : null error");
	}
	else {
		returnValue = atoi(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}

void gMysql::gradeMaxUpdate( char* userId , double grade )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USERSCORE_GRADEMAX_UPDATE, grade , userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

double gMysql::getGradeMax( char* userId )
{
	EnterCriticalSection(&dbLock);

	double returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_GRADEMAX_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getGradeMax() : null error");
	}
	else {
		returnValue = atof(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}

void gMysql::gradeSumUpdate( char* userId , double grade )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USERSCORE_GRADESUM_UPDATE, grade , userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

double gMysql::getGradeSum( char* userId )
{
	EnterCriticalSection(&dbLock);

	double returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_GRADESUM_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getGradeSum() : null error");
	}
	else {
		returnValue = atof(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}

void gMysql::gradeAvrUpdate( char* userId , double grade )
{
	EnterCriticalSection(&dbLock);
	
	char query[255];
	sprintf(query,USERSCORE_GRADEAVR_UPDATE, grade , userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

double gMysql::getGradeAvr( char* userId )
{
	EnterCriticalSection(&dbLock);

	double returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_GRADEAVR_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getGradeAvr() : null error");
	}
	else {
		returnValue = atof(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}

void gMysql::scoreUpdate( char* userId , int endTurn , int maxUser , int myRank )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	int addedScore = endTurn * (maxUser - myRank);
	sprintf(query,USERSCORE_SCORE_UPDATE, addedScore , userId);

	int query_stat = mysql_query(m_connection,query);

	if(query_stat != 0 ) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
	}
	LeaveCriticalSection(&dbLock);
}

int gMysql::getScore( char* userId )
{
	EnterCriticalSection(&dbLock);

	int returnValue = -1;
	char query[255];
	sprintf(query,USERSCORE_GRADEAVR_SELECT,userId);

	// sql�� ���� ���и�...
	// query_stat �� 0�� �ƴϸ� error�ΰ�����.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return -1;
	}

	// ���� ����� �޾Ƽ� password�� �޴� �κ�,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);

	if(sql_row == NULL) {
		fprintf(stderr,"getScore() : null error");
	}
	else {
		returnValue = atoi(sql_row[0]);
	}
	LeaveCriticalSection(&dbLock);
	return returnValue;
}

char* gMysql::commentGet( char* userId )
{	
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,USER_COMMENT_SELECT,userId);	

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}	

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* gotComment = new char [COMMENT_LENGTH];
	strcpy(gotComment,"");	

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL;
	}
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row == NULL) {
		fprintf(stderr,"commentGet() : null error");		
	}
	else {
		strcpy(gotComment , sql_row[0]);		
	}		

	LeaveCriticalSection(&dbLock);

	return gotComment;
}

int gMysql::getRank( char* userId )
{
	EnterCriticalSection(&dbLock);

	char query[255];
	sprintf(query,RANK_GRADEMAX_SELECT,userId);

	// ���� ����
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		LeaveCriticalSection(&dbLock);
		return NULL;
	}

	// ���� �м�
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	int gotGradeMaxRank = -1;

	if(arrLength == 0)
	{
		LeaveCriticalSection(&dbLock);
		return NULL;
	}
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row == NULL) {
		fprintf(stderr,"nicknameGet() : null error");
	}
	else {
		gotGradeMaxRank = atoi(sql_row[0]);
	}	
	LeaveCriticalSection(&dbLock);
	return gotGradeMaxRank;
}
