#define SOCKET int
//#include <windows.h>
//#include <winsock.h>
// 빈도수를 추가해 처음부터 다시 해야만 하는 운명이다.
#include <mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum eCOREMODE
{
	ECM_NONLOGIN,			// login 안한상태
	ECM_LOGIN,				// 얘는 걍 클라이언트에서 로그인 하기 위해 필요한 모드. 네트워크엔 관계없음
	ECM_BATTLENET,			// LOGIN 하면 이 모드


	ECM_TITLE,				// 타이틀
	ECM_PSEL,				// 플레이어 고르자
	ECM_CSEL,				// 캐릭터 고르자
	ECM_SUBMIT,				// 수강신청
	ECM_GAME,				// 게임
};

struct USER
{
	char		szID[16];
	char		szPW[16];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
};

#pragma comment(lib, "libmySQL.lib") 
#pragma comment(lib, "ws2_32.lib")   

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "autoset"
#define DB_NAME "mydb"

#define SQL_CREATE_TABLE "CREATE TABLE `mysql_api_test` (\
`index` int NOT NULL AUTO_INCREMENT PRIMARY KEY, \
`szID` VARCHAR(16) NULL ,\
`szPW` VARCHAR(16) NULL ,\
`coreWhere` int NULL,\
`nCoreFlag` int NULL \
) TYPE = MYISAM ;" //"

#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test`\
(`index`,  `szID` , `szPW`, `coreWhere`,`nCoreFlag` ) \
VALUES (\
NULL , '%s', '%s','%d','%d'\
);" //"

#define SQL_SELECT_RECORD "SELECT * FROM `mysql_api_test` \
WHERE szID = '%s'" //"
#define SQL_DROP_TABLE "DROP TABLE `mysql_api_test`"


class gMysql {
public:
	static gMysql	*GetIF();
private:
	MYSQL m_conn;
	MYSQL *m_connection;
	
public:
	void init();
	void put(char* id,char* pw,int coreWhere,int nCoreFlag);
	USER* get(char* id);
	void deleto();
};

static gMysql s_Mysql;

gMysql* gMysql::GetIF() 
{
	return &s_Mysql;
}

void gMysql::init() {
	//m_connection = NULL;
	
	char query[255];
	int query_stat;

	mysql_init(&m_conn);
	m_connection = mysql_real_connect(&m_conn,DB_HOST,
		DB_USER,DB_PASS,DB_NAME,3306,(char*)NULL,0);
	if(m_connection==NULL) {
		fprintf(stderr,"Mysql connection error : %s",mysql_error(&m_conn));
		return;
	}
	query_stat = mysql_query(m_connection,SQL_CREATE_TABLE);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s",mysql_error(&m_conn));
		return;
	}

}

void gMysql::put(char* id,char* pw,int coreWhere,int nCoreFlag) {
	char query[255];
	int query_stat;

	if(get(id)==NULL) {
		fprintf(stderr,"This ID %s is already existed\n",id);
	}

	sprintf(query,SQL_INSERT_RECORD,id,pw,coreWhere,nCoreFlag);
	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return;
	}
}

USER* gMysql::get(char* id) {
	// 다음 번에는 sql_row 를 return 하고 그 값을 받는 쪽으로 하는 것이 더 범용적임을
	// 명시한다.
	int query_stat;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	USER *user = new USER;

	char query[255];

	sprintf(query,SQL_SELECT_RECORD,id);

	query_stat = mysql_query(m_connection,query);
	if(query_stat != 0) {
		fprintf(stderr,"Mysql query error : %s\n",mysql_error(&m_conn));
		return NULL;
	}


	sql_result = mysql_store_result(m_connection);
	sql_row = mysql_fetch_row(sql_result);
	if(sql_row == NULL) return NULL;
	else {
		strcpy(user->szID,sql_row[1]);
		strcpy(user->szPW,sql_row[2]);
		user->coreWhere = (eCOREMODE)atoi(sql_row[3]);
		user->nCoreFlag = atoi(sql_row[4]);
		return user;
	}
}


void gMysql::deleto() {
	int query_stat = mysql_query(m_connection,SQL_DROP_TABLE);
	if(query_stat != 0) 
	{
		fprintf(stderr,"Mysql query error : %s",mysql_error(&m_conn));
		return;	
	}
	mysql_close(m_connection);
	return;
}


int main () {
	gMysql gmysql;
	USER* user;

	gmysql.init();
	gmysql.put("test1","1111",ECM_NONLOGIN,0);
	gmysql.put("test2","1112",ECM_NONLOGIN,0);
	
	user = gmysql.get("test1");
	if(user!=NULL)
		printf("%s %s %d %d\n",user->szID,user->szPW,user->coreWhere,user->nCoreFlag);
	user = gmysql.get("test2");
	if(user!=NULL)
		printf("%s %s %d %d\n",user->szID,user->szPW,user->coreWhere,user->nCoreFlag);

	gmysql.deleto();

}