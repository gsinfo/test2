public class CS
{

/* 
�Ʒ� �ڵ�� �ܺηκ��� tableName�� name�� ���� �޾Ƽ� SQL ������ �����ϰ� �ֽ��ϴ�. 
����, name������ name' OR 'a'=a�� �Է��ϸ� ���۵� ������ �����ϴ� ���ڿ� ������ �����մϴ�. 
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

		// ���Ⱦ��� : �ܺ� �Է°��� �������� �������� ���Ǿ� ����
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

		// ���Ⱦ��� : �ܺ� �Է°��� �������� �������� ���Ǿ� ����
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

		// ���Ⱦ��� : �ܺ� �Է°��� �������� �������� ���Ǿ� ����
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

		// ���Ⱦ��� : �ܺ� �Է°��� �������� �������� ���Ǿ� ����
		rs = stmt.executeQuery("SELECT * FROM " + props.getProperty("jdbc.tableName") + "WHERE Name = " + props.getProperty("jdbc.name");
		//...
  	}
	catch (SQLException e) { 
		//... 
	}
	//...
}

/*
�Ķ���͸� �޴� perparedStatment ��ü�� ��� ��Ʈ������ �����ϰ�, �Ķ���� �κ��� setXXX �޼ҵ�� �����Ͽ�, �ܺ� �Է��� �������� ������ �ٲٴ� ���� ������ �� �ֽ��ϴ�.
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
		
		// ���� : �����ϵ� ������ ���
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

