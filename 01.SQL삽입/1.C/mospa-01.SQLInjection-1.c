#include <stdlib.h>
#include <sql.h>

/*
�Ʒ� �ڵ�� �ܺηκ��� �������� �޾Ƽ� SQL ������ �����ϰ� �ֽ��ϴ�. 
����, �ƹ� �������� ���ǹǷ� ���Ѿ��� DB �۾��� �����ϹǷ� ����մϴ�.
*/
void Sql_process(SQLHSTMT sqlh)
{ 
	char * query = getent("query_string");
	
	// ���Ⱦ��� : �ܺ� �Է°��� �������� SQL �������� ���
	SQLExecDirect(sqlh, query, SQL_NTS);
}

/*
�������� �̸� ���ǵǾ� �־� ������ DB �۾��� �����ϹǷ� �����ϴϴ�.
*/
void Sql_process(SQLHSTMT sqlh)
{
	// ���� : ���ȭ�� ������ ���
	char * query = "select * from items";
	SQLExecDirect(sqlh, query, SQL_NTS);
}