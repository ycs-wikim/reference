<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<% request.setCharacterEncoding("UTF-8"); %>
    <%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<link href="css/boardwrite_css.css" type="text/css" rel = "stylesheet">
<link rel="stylesheet"
	href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">

<title>글 수정</title>
</head>
<body>
<%
String b_title = null; //게시글 제목
String b_writer = null; //작성자
String b_content = null; //게시글 내용

String id = request.getParameter("id");
String type = request.getParameter("type");
String name = (String)session.getAttribute("Name");
String manager = (String)session.getAttribute("MName");

Connection conn = null;
PreparedStatement pstmt = null;
ResultSet rs = null;

try{
	String jdbcUrl = "jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
	String dbId = "admin";
	String dbPass = "password";
	Class.forName("com.mysql.jdbc.Driver");
	conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
	
	//sql문으로 db에 제목, 작성자, 내용 검색
	String sql = "select title, writer, wrcontent from board where boardid=?";
	pstmt = conn.prepareStatement(sql);
	pstmt.setString(1, id);
	rs = pstmt.executeQuery();
	
	//각각의 결과 레코드를 변수에 입력
	while(rs.next()){
		b_title = rs.getString("title");
		b_writer = (String)rs.getString("writer");
		b_content = rs.getString("wrcontent");
	}

%>
<jsp:include page = "top.jsp" flush = "false"/>
<form action="boardwrite.jsp" method="post">
	
	<fieldset>
	<div class = "board_position">
	<div style = "margin-top:20px;">
	<h3>&nbsp;작성 게시글</h3>
	</div>
	<table class="table">
	<tr><th>제목</th><th><p rows= "1" style="font-weight:500"><%=b_title%></p>
</th></tr>
	<tr><td>작성자</td><td><p><%=b_writer%></p></td></tr>
	 
    <tr><td>글 내용</td><td><p cols = "80" rows = "20" ><%=b_content%></p></td></tr>
  </table>
	<input type="hidden" value="<%=id%>" name="title">
	<input type="hidden" value="<%=type%>" name="kind">
  
  <%
  if(name == null && manager == null){
		name = "name";
  }else if(manager != null){
	  name = "admin";
	  b_writer = "admin";
  }
	if(name.equals(b_writer)){
		 %>

	 <button type="submit" class="btn1">현재 글 수정</button>
	 <button type="button" class="btn1" onclick="javascript:location.href='delete.jsp?kind=<%=type%>&id=<%=id%>'">현재 글 삭제</button>
	 <button type="button" class="btn1" onclick="javascript:history.back()">이전 글 목록</button>
	 </form>
	 <%
	}
  	else{
  		%>
  		 <button type="button" class="btn1" onclick="javascript:history.back()">이전 글 목록</button>
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
  </div>
  </fieldset>
</body>
</html>
