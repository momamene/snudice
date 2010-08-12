#include <mysql.h>

#pragma comment(lib, "libmySQL.lib") 
#pragma comment(lib, "ws2_32.lib")   


////////////////////////////////////////////////////////////////////////

#define SOCKET int
//#include <windows.h>
//#include <winsock.h>
#include <mysql.h>
#include <string.h>
#include <stdio.h>

#pragma comment(lib, "libmySQL.lib") 
#pragma comment(lib, "ws2_32.lib")   

//#define DB_HOST "220.66.31.182"
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "autoset"
#define DB_NAME "mydb"

#define SQL_CREATE_TABLE "CREATE TABLE `mysql_api_test` (\
`id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY ,\
`num` INT NULL ,\
`string` VARCHAR( 20 ) NULL \
) TYPE = MYISAM ;" //"
#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test` ( `id` , `num` , `string` ) \
VALUES (\
NULL , '%d', '%s'\
);" //"
#define SQL_SELECT_RECORD "SELECT * FROM `mysql_api_test`"
#define SQL_DROP_TABLE "DROP TABLE `mysql_api_test`"

int main2()
{
	MYSQL *connection=NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

	char query[255];

	mysql_init(&conn);
	// DB 연결
	connection = mysql_real_connect(&conn, DB_HOST,
		DB_USER, DB_PASS,DB_NAME, 3306,(char *)NULL, 0);
	if(connection==NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}
	// 테이블 생성
	query_stat=mysql_query(connection,SQL_CREATE_TABLE);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	// 레코드 삽입
	for(int i=0;i<5;i++)
	{  
		sprintf(query,SQL_INSERT_RECORD,100+i,"DB테스트");
		query_stat = mysql_query(connection, query);
		if (query_stat != 0)
		{
			fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
			return 1;
		}
	}
	// 셀렉트
	query_stat=mysql_query(connection,SQL_SELECT_RECORD);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	// 결과 출력
	sql_result=mysql_store_result(connection);
	while((sql_row=mysql_fetch_row(sql_result))!=NULL)
	{
		printf("%s %s %s\n",sql_row[0],sql_row[1],sql_row[2]);
	}
	mysql_free_result(sql_result);

	
	// 테이블 삭제
	query_stat=mysql_query(connection,SQL_DROP_TABLE);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	

	// DB 연결 닫기
	mysql_close(connection);
	return 0;
}

///////////////////////////////////////////////////////////////////
//[출처] [본문스크랩] [그리즐리의 ATL/MFC 팁] MySQL 시작하기|작성자 옹식이

