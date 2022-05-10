<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.Enumeration" %>
<%    
	//Enumeration memck = request.getParameterNames(); //manageform.jsp에서 넘어온 stdid값 배열
	String memck [] = request.getParameterValues("memck");
	String id = null;
    int i;
    Connection conn = null;
    PreparedStatement pstmt = null;
    String sql = null;
    try{
    	String jdbcUrl = "jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
		String dbId = "admin";
		String dbPass = "password";
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
			for(i = 0; i < memck.length; i++){
				//sql문으로 db에 chk배열의 학번의 승인여부를 'O' 로 업데이트
				id = memck[i];
				sql = "delete from member where id = ?";
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, id);
				pstmt.executeUpdate();
			}
		%>
		<script>
			alert("가입 거절이 완료되었습니다.");
			location.href="manageform.jsp";
    	</script>
		<%
	    }catch(SQLException ex){
	    	ex.printStackTrace();
	    }catch(NullPointerException exx){
			%>
			<script>
				alert("거절할 사람을 선택해주세요.")
				location.href="manageform.jsp";
	    	</script>
			<%
	    }
    	finally {
			if (pstmt != null)
				try {pstmt.close();} catch (SQLException sqle) {}
			if (conn != null)
				try {conn.close();} catch (SQLException sqle) {}
	    }
    %>