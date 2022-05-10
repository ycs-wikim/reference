<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>

<link rel="stylesheet" type="text/css" href="css/table.css" />
</head>

<body>
<div class="list">
	<legend>공지사항</legend>	
	
	<table class="table">
	<tr><th>No.</th><th>제목</th><th>작성자</th><th>작성일</th></tr>
	<%
	String b_num = null; //게시글 번호
    String b_title = null; //게시글 제목
    String b_writer = null; //게시글 작성자
    String b_date = null; //게시글 날짜
    String kind="notice";
    
	Connection conn = null;
	PreparedStatement pstmt = null;
	ResultSet rs = null;
	String sql;
	try{
		
		String jdbcUrl = "jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
		String dbId = "admin";
		String dbPass = "password";
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
		sql = "select boardid, title, boardtype, writer, wrdate from board where boardtype=? order by boardid desc limit 5";
		pstmt = conn.prepareStatement(sql);
		pstmt.setString(1, kind);
		rs = pstmt.executeQuery();
		
		//각각의 결과 레코드를 변수에 입력
		while(rs.next()){
			b_num = rs.getString("boardid");
			b_title = rs.getString("title");
			b_writer = rs.getString("writer");
			b_date = rs.getString("wrdate");
			%>
		<tr><td><%=b_num%></td>
		<td><a href="modify.jsp?id=<%=b_num%>&type=notice"><%=b_title%></a></td>
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
<a href="AI.jsp?kind=notice" class="" style="padding-left: 49em">전체보기</a>
	</div>
</body>
</html>