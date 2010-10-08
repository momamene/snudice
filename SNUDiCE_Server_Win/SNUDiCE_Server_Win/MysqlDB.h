#include <mysql.h>
#include "network.h"

//#define DB_HOST "211.169.219.71"
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "apmsetup"
#define DB_NAME "mydb"



#define SQL_CREATE_TABLE "CREATE TABLE `mysql_api_test` (\
`index` int NOT NULL AUTO_INCREMENT PRIMARY KEY, \
`szID` VARCHAR(16) NULL ,\
`szPW` VARCHAR(16) NULL \
) TYPE = MYISAM ;" //"

#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test`\
(`index`,  `szID` , `szPW`) \
VALUES (\
NULL , '%s', '%s'\
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
	void put(char* id,char* pw);
	USER* get(char* id);
	void deleto();
	void release();
};