public class CS
{

/* 
아래 코드는 외부로부터 tableName과 name의 값을 받아서 SQL 쿼리를 생성하고 있습니다. 
만약, name값으로 name' OR 'a'=a를 입력하면 조작된 쿼리를 생성하는 문자열 전달이 가능합니다. 
*/
public void bad1()
{ 
	java.sql.Statement stmt;
	Connection con;
	ResultSet rs;
	//...

	try {
		String tableName = props.getProperty("jdbc.tableName");
		String name = props.getProperty("jdbc.name");
		String query = "SELECT * FROM " + tableName + "WHERE Name = " + name;
		stmt = con.createStatment();

		// 보안약점 : 외부 입력값이 검증없이 쿼리문에 사용되어 실행
		rs = stmt.executeQuery(query);
		//...
  	}
	catch (SQLException e) { 
		//... 
	}
	//...
}

public void bad2()
{ 
	java.sql.Statement stmt;
	Connection con;
	ResultSet rs;
	//...

	try {
		String name;
		int byteCount = System.in.read( name );
		String query = "SELECT * FROM " + tableName + "WHERE Name = " + name;
		stmt = con.createStatment();

		// 보안약점 : 외부 입력값이 검증없이 쿼리문에 사용되어 실행
		rs = stmt.executeQuery(query);
		//...
  	}
	catch (SQLException e) { 
		//... 
	}
	//...
}

/*public void bad3(String name)
{ 
	java.sql.Statement stmt;
	Connection con;
	ResultSet rs;
	//...

	try {
		String query = "SELECT * FROM " + tableName + "WHERE Name = " + name;
		stmt = con.createStatment();

		// 보안약점 : 외부 입력값이 검증없이 쿼리문에 사용되어 실행
		rs = stmt.executeQuery(query);
		//...
  	}
	catch (SQLException e) { 
		//... 
	}
	//...
}*/

public void bad4()
{ 
	java.sql.Statement stmt;
	Connection con;
	ResultSet rs;
	//...

	try {
		stmt = con.createStatment();

		// 보안약점 : 외부 입력값이 검증없이 쿼리문에 사용되어 실행
		rs = stmt.executeQuery("SELECT * FROM " + props.getProperty("jdbc.tableName") + "WHERE Name = " + props.getProperty("jdbc.name");
		//...
  	}
	catch (SQLException e) { 
		//... 
	}
	//...
}

/*
파라미터를 받는 perparedStatment 객체를 상수 스트링으로 생성하고, 파라미터 부분을 setXXX 메소드로 설정하여, 외부 입력이 쿼리문의 구조를 바꾸는 것을 방지할 수 있습니다.
*/
public void good()
{ 
	java.sql.Statement stmt;
	Connection con;
	ResultSet rs;
	//...

	try {
		String tableName = props.getProperty("jdbc.tableName");
		String name = props.getProperty("jdbc.name");
		
		// 수정 : 컴파일된 쿼리문 사용
		String query = "SELECT * FROM ? WHERE Name = ?";
		stmt = con.prepareStatement(query);
		stmt.setString(1, tableName);
		stmt.setString(2, name);
		rs = stmt.executeQuery();
		//...
  	}
	catch (SQLException e) { 
		//... 
	}
	//...
}

}

