static SQLHSTMT statmentHandle;
const char * GetParameter(const char * queryString, const char * key);
static const char * GET_USER_INFO_CMD = "get_user_info";
static const char * USER_ID_PARAM = "user_id";
static const char * PASSWORD_PARAM = "password";
static const int MAX_QUERY_LENGTH = 256;
const int EQUAL = 0;

/*
�Ʒ��� �������� queryStr�κ��� �޾ƿ� �ܺ� �Է¿��� user_id�� password�� �ش��ϴ� ���� �߶�� �� SQL���� ���ڰ����� �״�� ����Ͽ���. 
user_id�� �ش��ϴ� �Է°����� name' OR 'a'='a��--�� ���� ���ڿ��� �ָ� WHERE ���� �׻� ���� �Ǿ� user_id�� ������� �����κ��� ����� �� �ְ� �ȴ�.
*/
int bad(void)
{
	SQLCHAR * queryStr;
	queryStr = getenv("QUERY_STRING");
	if (queryStr == NULL)
	{
		// Error
		//...
	}
	// �Է°�
	char * command = GetParameter(queryStr, "command");
	if (strcmp(command, GET_USER_INFO_CMD) == EQUAL)
	{
		const char * userId = GetParameter(queryStr, USER_ID_PARAM);
		const char * password = GetParameter(queryStr, PASSWORD_PARAM);

		char query[MAX_QUERY_LENGTH];
		sprintf(query, "SELECT * FROM members WHERE username= '%s' AND password = '%s'", userId, password);
		// ���Ⱦ��� 
		SQLExecDirect(statmentHandle, query, SQL_NTS);
	}
	
	return 0;
}

/*
������ ������ http request�κ��� ������ ����� ID�� ��ȣ�� makeSecureString�Լ��� �̿��Ͽ� ������ SQL���� ������ ���� �� �ִ� �ܾ��� Ư�����ڸ� �����Ͽ���.
���� ���� ������ ����� ID�� ��ȣ�� �߰��ϱ� ���鵵��, ����� ID�� ��ȣ�� ���̸� �����Ͽ���.
*/
int good(void)
{
	SQLCHAR * queryStr;
	queryStr = getenv("QUERY_STRING");
	if (queryStr == NULL)
	{
		// Error
		//...
	}
	// �Է°�
	char * command = GetParameter(queryStr, "command");
	if (strcmp(command, GET_USER_INFO_CMD) == EQUAL)
	{
		const char * userId = GetParameter(queryStr, USER_ID_PARAM);
		userId = makeSecureString(userId, MAX_USER_LENGTH);
		const char * password = GetParameter(queryStr, PASSWORD_PARAM);
		password = makeSecureString(password, MAX_USER_LENGTH);

		char query[MAX_QUERY_LENGTH];
		sprintf(query, "SELECT * FROM members WHERE username= '%s' AND password = '%s'", userId, password);
		// ���� 
		SQLExecDirect(statmentHandle, query, SQL_NTS);
	}
	
	return 0;
}

const char * makeSecureString(const char *str, int maxLength)
{
	char * buffer = (char *) malloc(maxLength + 1);
	char * originalStr = (char *)malloc(maxLength + 1);
	
	strncpy(originalStr, str, maxLength);
	originalStr[maxLength] = NULL;
	regmatch_t mt;
	const char * currentPos = originalStr;
	while (regexec(&unsecurePattern, currentPos, 1, &mt, REG_NOTBOL) == 0)
	{
		strncat(buffer, currentPos, mt.rm_so);
		currentPos += mt.rm_eo;
	}
	strcat(buffer, currentPos);
	free(originalStr);
	return buffer;
}