<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<%    
	String chk[] = request.getParameterValues("chk"); //manageform.jsp에서 넘어온 boardid값 배열
	String id = request.getParameter("id"); //modify.jsp에서 받아온 boardid값
    String writer = (String)session.getAttribute("Name"); //로그인 한 사람의 이름
    String manager = (String)session.getAttribute("MName"); //마스터 로그인 시
    String type = request.getParameter("kind"); //게시판 종류
    String check = request.getParameter("check");
    int i_check;
    if(check == null)
    	i_check = 0;
    else
    	i_check = Integer.parseInt(check);
    
    int i;
    
    if(writer == null && manager == null){
    	%>
    	<script>
    	alert("로그인 후 이용 가능합니다.");
    	location.href="AI.jsp?kind=type";
    	</script>
    	<%
    }
    else{
    
    Connection conn = null;
    PreparedStatement pstmt = null;
    String sql = null;
    try{
    	String jdbcUrl = "jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
		String dbId = "admin";
		String dbPass = "password";
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
		
		if(i_check == 1){
		for(i = 0; i < chk.length; i++){
		//sql문으로 db에 번호, 제목, 작성자, 종류, 날짜 검색
		sql = "delete from board where boardid=?";
		pstmt = conn.prepareStatement(sql);
		pstmt.setInt(1, Integer.parseInt(chk[i]));
		pstmt.executeUpdate();
		}}
		else{
			sql = "delete from board where boardid=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, Integer.parseInt(id));
			pstmt.executeUpdate();
		}

		%>
		<script>
		var check = <%=i_check%>;
		if(check == 0)
    		location.href="AI.jsp?kind=<%=type%>";
		else
			location.href="manageform.jsp";
    	</script>
		<%
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
	    }
    %>
</body>
</html>