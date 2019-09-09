static SQLHSTMT statmentHandle;
const char * GetParameter(const char * queryString, const char * key);
static const char * GET_USER_INFO_CMD = "get_user_info";
static const char * USER_ID_PARAM = "user_id";
static const char * PASSWORD_PARAM = "password";
static const int MAX_QUERY_LENGTH = 256;
const int EQUAL = 0;

/*
아래의 예에서는 queryStr로부터 받아온 외부 입력에서 user_id와 password에 해당하는 값을 잘라온 후 SQL문의 인자값으로 그대로 사용하였다. 
user_id에 해당하는 입력값으로 name' OR 'a'='a‘--와 같은 문자열을 주면 WHERE 절이 항상 참이 되어 user_id에 상관없이 인증부분을 통과할 수 있게 된다.
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
	// 입력값
	char * command = GetParameter(queryStr, "command");
	if (strcmp(command, GET_USER_INFO_CMD) == EQUAL)
	{
		const char * userId = GetParameter(queryStr, USER_ID_PARAM);
		const char * password = GetParameter(queryStr, PASSWORD_PARAM);

		char query[MAX_QUERY_LENGTH];
		sprintf(query, "SELECT * FROM members WHERE username= '%s' AND password = '%s'", userId, password);
		// 보안약점 
		SQLExecDirect(statmentHandle, query, SQL_NTS);
	}
	
	return 0;
}

/*
다음의 예제는 http request로부터 추출한 사용자 ID와 암호를 makeSecureString함수를 이용하여 위험한 SQL구문 생성에 쓰일 수 있는 단어들과 특수문자를 제거하였다.
또한 공격 구문을 사용자 ID와 암호에 추가하기 힘들도록, 사용자 ID와 암호의 길이를 제한하였다.
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
	// 입력값
	char * command = GetParameter(queryStr, "command");
	if (strcmp(command, GET_USER_INFO_CMD) == EQUAL)
	{
		const char * userId = GetParameter(queryStr, USER_ID_PARAM);
		userId = makeSecureString(userId, MAX_USER_LENGTH);
		const char * password = GetParameter(queryStr, PASSWORD_PARAM);
		password = makeSecureString(password, MAX_USER_LENGTH);

		char query[MAX_QUERY_LENGTH];
		sprintf(query, "SELECT * FROM members WHERE username= '%s' AND password = '%s'", userId, password);
		// 수정 
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