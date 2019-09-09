#include <stdlib.h>
#include <sql.h>

/*
아래 코드는 외부로부터 쿼리문을 받아서 SQL 쿼리를 생성하고 있습니다. 
만약, 아무 검증없이 사용되므로 제한없이 DB 작업이 가능하므로 취약합니다.
*/
void Sql_process(SQLHSTMT sqlh)
{ 
	char * query = getent("query_string");
	
	// 보안약점 : 외부 입력값이 검증없이 SQL 쿼리문에 사용
	SQLExecDirect(sqlh, query, SQL_NTS);
}

/*
쿼리문이 미리 정의되어 있어 정해진 DB 작업만 가능하므로 안전하니다.
*/
void Sql_process(SQLHSTMT sqlh)
{
	// 수정 : 상수화된 쿼리문 사용
	char * query = "select * from items";
	SQLExecDirect(sqlh, query, SQL_NTS);
}