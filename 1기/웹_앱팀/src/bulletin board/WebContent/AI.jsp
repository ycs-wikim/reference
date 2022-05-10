<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<% request.setCharacterEncoding("UTF-8"); %>
<%@ page import="java.sql.*" %>
<%@ page import="java.lang.*" %>
<!DOCTYPE>
<html>
<head>
<style type="text/css">
.tableA {
	  width:850px; 
	  height:40px;
      border-collapse: collapse;
      border-top: 3px solid #343A40;     
}  
    .tableA th {
      color: #343A40;
      background: #D6EEF2;
      text-align: center;
    }
    .tableA th, .tableA td {
      padding: 10px;
      border: 1px solid #ddd;
    }
    .tableA th:first-child, .tableA td:first-child {
      border-left: 0;
    }
    .tableA th:last-child, .tableA td:last-child {
      border-right: 0;
    }
    .tableA tr td:first-child{
      text-align: center;
    }
    
.buttonA {
	float:right;
	border: 1.5px solid #343A40;
	width: 150px;
	margin: 10px;
	font-weight: 400;
	color: #343A40;
	padding: 8px 25px;
	cursor: pointer;
	border-radius: 100px;
}
 

.btnA {
	border-radius: 100px;
	margin-bottom:20px;
	margin-right:10px;
	float:right;
}

.number {
	text-decoration: none;
	color:#000000;
}

form{

	 margin : 10px;
}

fieldset { 
border: 2px solid #343A40;
padding: 10px;
margin: 10px;
}


a, a:hover {

	text-decoration: none;

}
textarea {
	width: 100%;
	border: none;
	resize: none;
}

</style>
<title>레퍼런스 웹/앱팀</title>
<link href="css/board.css" type="text/css" rel = "stylesheet">
</head>

<body>
<jsp:include page = "top.jsp" flush = "false"/>
<%!
double total; //게시판마다 게시글이 총 몇개인지 확인
int board_num; //한페이지에 10개씩 몇 페이지 나오는지 확인 올림처리 
%>

<%
String kind = (String)request.getParameter("kind");
String manager = (String)session.getAttribute("MName");
String name = "";
String s_page = request.getParameter("page");
int page_num;
if(s_page == null)
	page_num = 1;
else
	page_num = Integer.parseInt(s_page);

switch(kind){

case "web" :
   name = "웹/앱 팀";
   break;
case "ai" :
   name = "인공지능 팀";
   break;
case "net" :
   name = "네트워크 팀";
   break;
case "game" :
   name = "게임 팀";
   break;
case "daily" :
   name = "일상";
   break;
case "notice" :
	   name = "공지사항";
	   break;
}
%>
<!-- 전체를 정렬할 container -->
<div class = "sort-main">
<jsp:include page = "info.jsp" flush = "false"/>
<!-- 게시판과 페이지 버튼 게시글 작성을 정렬할 container -->
<div class = "sort-block">
<div class="list">

   <legend> <%=name %> 게시판</legend>   
   <table class="tableA">
   <tr><th>No.</th><th>제목</th><th>작성자</th><th>작성일</th></tr>
    <%
    String b_num = null; //게시글 번호
    String b_title = null; //게시글 제목
    String b_writer = null; //게시글 작성자
    String b_date = null; //게시글 날짜
    
    Connection conn = null;
    PreparedStatement pstmt = null;
    ResultSet rs = null;
    try{
    	String jdbcUrl = "jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
		String dbId = "admin";
		String dbPass = "password";
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
		
		String sql = "select count(*) from board where boardtype=?";
		pstmt = conn.prepareStatement(sql);
		pstmt.setString(1, kind);
		rs = pstmt.executeQuery();
		
		while(rs.next()){
			total = rs.getInt(1); //몇개인지 확인
		}
		int num = (int)total+1;
		total = total/10;
		board_num = (int)Math.ceil(total);
		
		//sql문으로 db에 번호, 제목, 작성자, 종류, 날짜 검색
		sql = "select boardid, title, boardtype, writer, wrdate from board where boardtype=? order by boardid desc limit ?,?";
		pstmt = conn.prepareStatement(sql);
		pstmt.setString(1, kind);
		pstmt.setInt(2, (page_num-1)*10);
		pstmt.setInt(3, 10);
		rs = pstmt.executeQuery();
		
		//각각의 결과 레코드를 변수에 입력
		while(rs.next()){
			b_num = rs.getString("boardid");
			b_title = rs.getString("title");
			b_writer = rs.getString("writer");
			b_date = rs.getString("wrdate");
			%>
		<tr><td><%=b_num%></td>
		<td><a href="modify.jsp?id=<%=b_num%>&type=<%=kind%>"><%=b_title%></a></td>
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
<%
int i;
%>
	<div style="display: inline-block; margin:auto; align-items: center;">
	<br>
	<%
	for(i=1; i<=board_num; i++){
	%>
	<a href="AI.jsp?kind=<%=kind%>&page=<%=i%>" class="number" style="margin: 20px;"><%=i%></a>
	<%} %>
	</div>
		<div style="display: inline-block; margin:  0px; float: right;">
		<%
		
		if(name == "공지사항"){
			if(manager != null){
				%>
				<button type="button" class="buttonA" style="float:right;" onclick="location.href='boardwrite.jsp?kind=<%=kind%>'">게시글 작성</button>
				<%
			}
			else{
					
				}
		}else{
			%>
		<button type="button" class="buttonA" style="float:right;" onclick="location.href='boardwrite.jsp?kind=<%=kind%>'">게시글 작성</button>
		<%
		}
		%>
		</div>
</div>
</div>
</body>
</html>