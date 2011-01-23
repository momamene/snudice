#include "mysqlDB.h"


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
	char query[255];
	int query_stat;

	if(get(id)!=NULL) {
		fprintf(stderr,"This ID %s is already existed\n",id);
		return;
	}


	sprintf(query,SQL_INSERT_RECORD,id,pw);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return;
	}
}


USER* gMysql::get(char* userId) {
	USER *user = new USER;
	char*	pass;
	strcpy(user->szID , userId);

	pass = passwordGet(userId);
	if(pass)
	{
		strcpy(user->szPW, pass);
		delete pass;
	}

	return user;
}

char* gMysql::passwordGet(char* userId) {

	char* password = new char[33];
	char query[255];
	sprintf(query,USER_SELECT,userId);

	// sql의 성공 실패를...
	// query_stat 이 0이 아니면 error인가보다.
	int query_stat = mysql_query(m_connection, (TCHAR*)query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		delete password;
		return NULL;
	}

	// 쿼리 결과를 받아서 password를 받는 부분,
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	MYSQL_ROW sql_row = mysql_fetch_row(sql_result);
	if(sql_row != NULL) {
		strncpy(password,sql_row[0],33);
	}
	else {
		strcpy(password,"");
	}
	return password;

}

void gMysql::friendPutOne(char* userId, char* friendId) {
	char query[255];
	int query_stat;

	if(isFriendOneExisted(userId,friendId)) {
		fprintf(stderr,"Friend Connection %s - %s is already existed\n",userId,friendId);
		return;
	}

	sprintf(query,FRIEND_INSERT,userId,friendId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return;
	}
}

// 너무 막장이고 잘 돌아가는 지 확신이 안든다.
// 좀 더 많은 테스트를 거칠것
bool gMysql::isFriendOneExisted(char* userId, char* friendId) {

	char query[255];
	sprintf(query,FRIEND_SELECT_AND,userId,friendId);

	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return false;
	}

	MYSQL_RES* sql_resultA = mysql_store_result(m_connection);
	int count = mysql_num_rows(sql_resultA);
	if(count != 0) {
		return true;
	}

	sprintf(query,FRIEND_SELECT_AND,friendId,userId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return false;
	}

	MYSQL_RES* sql_resultB = mysql_store_result(m_connection);
	count = mysql_num_rows(sql_resultB);
	if(count != 0) {
		return true;
	}
	return false;
}

// 동적인 변수를 return 한다.
// 이건 심각한 문제일려나...
// 다 쓴 다음에 변수를 delete 해주면 좋을 것 같다.
// "test1,test2,test3,test4"
char* gMysql::friendGet(char* userId) {

	char query[255];
	sprintf(query,FRIEND_SELECT_OR,userId,userId);

	// 쿼리 수행
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return NULL;
	}

	// 수행 분석
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* friendArr = new char [arrLength*17];
	strcpy(friendArr,"");

	if(arrLength == 0) return NULL; // 아무도 친구가 없을때 

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


	return friendArr;
}

bool gMysql::friendDeleteOne(char* userId, char* friendId) {

	char query[255];
	sprintf(query,FRIEND_DELETE,userId,friendId);
	int query_statA = mysql_query(m_connection,query);

	sprintf(query,FRIEND_DELETE,friendId,userId);
	int query_statB = mysql_query(m_connection,query);

	if(query_statA != 0 && query_statB != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return NULL;
	}

}

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





//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void gMysql::blockPutOne(char* userId, char* blockId) {
	char query[255];
	int query_stat;

	if(isBlockOneExisted(userId,blockId)) {
		fprintf(stderr,"Block Connection %s - %s is already existed\n",userId,blockId);
		return;
	}

	sprintf(query,BLOCK_INSERT,userId,blockId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return;
	}
}

// 너무 막장이고 잘 돌아가는 지 확신이 안든다.
// 좀 더 많은 테스트를 거칠것
bool gMysql::isBlockOneExisted(char* userId, char* blockId) {

	char query[255];
	sprintf(query,BLOCK_SELECT_AND,userId,blockId);

	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return false;
	}

	MYSQL_RES* sql_resultA = mysql_store_result(m_connection);
	int count = mysql_num_rows(sql_resultA);
	if(count != 0) {
		return true;
	}

	sprintf(query,BLOCK_SELECT_AND,blockId,userId);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return false;
	}

	MYSQL_RES* sql_resultB = mysql_store_result(m_connection);
	count = mysql_num_rows(sql_resultB);
	if(count != 0) {
		return true;
	}
	return false;
}

// 동적인 변수를 return 한다.
// 이건 심각한 문제일려나...
// 다 쓴 다음에 변수를 delete 해주면 좋을 것 같다.
// "test1,test2,test3,test4"
char* gMysql::blockGet(char* userId) {

	char query[255];
	sprintf(query,BLOCK_SELECT_OR,userId,userId);

	// 쿼리 수행
	int query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return NULL;
	}

	// 수행 분석
	MYSQL_RES* sql_result = mysql_store_result(m_connection);
	int arrLength = mysql_num_rows(sql_result);

	char* blockArr = new char [arrLength*17];
	strcpy(blockArr,"");

	if(arrLength == 0) return NULL;

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


	return blockArr;
}

bool gMysql::blockDeleteOne(char* userId, char* blockId) {

	char query[255];
	sprintf(query,BLOCK_DELETE,userId,blockId);
	int query_statA = mysql_query(m_connection,query);

	sprintf(query,BLOCK_DELETE,blockId,userId);
	int query_statB = mysql_query(m_connection,query);

	if(query_statA != 0 && query_statB != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return NULL;
	}

}


