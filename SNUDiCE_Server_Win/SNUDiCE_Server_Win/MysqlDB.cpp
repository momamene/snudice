#include "MysqlDB.h"


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

void gMysql::release() {
	mysql_close(m_connection);
}