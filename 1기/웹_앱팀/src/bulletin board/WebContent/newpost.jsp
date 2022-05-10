<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<link href="css/table.css" type="text/css" rel = "stylesheet">
</head>
<style type="text/css">

.table {
      border-collapse: collapse;
      border-top: 3px solid #343A40;
    }  
    .table th {
      color: #343A40;
      background: #D6EEF2;
      text-align: center;
    }
    .table th, .table td {
      padding: 10px;
      border: 1px solid #ddd;
    }
    .table th:first-child, .table td:first-child {
      border-left: 0;
    }
    .table th:last-child, .table td:last-child {
      border-right: 0;
    }
    .table tr td:first-child{
      text-align: center;
    }
    
button {
border: 1.5px solid #343A40;
width: 150px;
margin : 10px;
font-weight: 400;
color: #343A40;
padding: 8px 25px; 
cursor:pointer;
border-radius:100px;
}    

form{
margin : 10px;
}

fieldset { 
border: 2px solid #343A40;
padding: 10px;
margin: 10px;
}

</style>
</head>

<!DOCTYPE>

<html>

<head>

<body>
<div class="list">

	<legend>최근 게시글</legend>	
	<br>
	<table class="table notice">
	<tr><th>No.</th><th>제목</th><th>작성자</th><th>작성일</th></tr>
    <%
    String b_num = null; //게시글 번호
    String b_title = null; //게시글 제목
    String b_writer = null; //게시글 작성자
    String b_date = null; //게시글 날짜
    String b_type = null; // 게시판 타입
    
    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;
    try{
    	String jdbcUrl = "jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
		String dbId = "admin";
		String dbPass = "password";
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
		
		//sql문으로 db에 번호, 제목, 작성자, 종류, 날짜 검색
		String sql = "select boardid, title, boardtype, writer, wrdate from board order by boardid desc limit 5";
		pstmt = conn.prepareStatement(sql);
		rs = pstmt.executeQuery();
		
		//각각의 결과 레코드를 변수에 입력
		while(rs.next()){
			b_num = rs.getString("boardid");
			b_title = rs.getString("title");
			b_type = rs.getString("boardtype");
			b_writer = rs.getString("writer");
			b_date = rs.getString("wrdate");
			
			%>
		<tr><td><%=b_num%></td>
		<td><a href="modify.jsp?id=<%=b_num%>&type=<%=b_type%>"><%=b_title%></a></td>
		<td><%=b_writer%></td>
		<td><%=b_date%></td></tr>
		<%
		}
    }catch(SQLException ex){
    	ex.printStackTrace();
    } finally {
		if (pstmt != null)
		try {
			pstmt.close();
		} catch (SQLException sqle) {
		}

		if (conn != null)
		try {
			conn.close();
		} catch (SQLException sqle) {
		}
		}
    %>
  </table> 
</div>
</body>
</html>