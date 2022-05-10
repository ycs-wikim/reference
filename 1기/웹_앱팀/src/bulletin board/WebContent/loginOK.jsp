<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="java.util.*" %>
<%@ page import="java.sql.*"%>
	<% 
	// 관리자 전용 ID/PW
	String MasterID = (String)application.getInitParameter("MasterID");
	String MasterPW = (String)application.getInitParameter("MasterPassword");
    String MasterName = (String)application.getInitParameter("MasterName");
    String sign = "O";
    
    // login.jsp에서 POST로 받아온 값
    String id = request.getParameter("id");
    String pw = request.getParameter("pw");
    
    // DB에서 id에 맞는 정보들을 가져온 값
    String SelectID = null;
    String SelectPW = null;
    String Name = null;
    String signcheck = null;
    String stdid = null;
    
    
    // DB연결
    Connection conn=null;
	PreparedStatement pstmt = null;
	String str = "";
	String prnM=null;
	
	try{
       String jdbcUrl="jdbc:mysql://localhost:3306/web_ref_db?useUnicode=yes&characterEncoding=UTF8";
    String dbId="admin";
    String dbPass="password";
    Class.forName("com.mysql.jdbc.Driver");
    conn = DriverManager.getConnection(jdbcUrl, dbId, dbPass);
    
    // SQL문으로 DB내에서 로그인하려는 ID와 PW 이름 검색
    String sql = "select stdid, id, passwd, name, signcheck from member where id = ?";
    pstmt = conn.prepareStatement(sql);
    pstmt.setString(1, id);
    ResultSet result = pstmt.executeQuery();
    
    // 결과 레코드 하나씩마다 ID PW 이름 변수에 입력
    while(result.next())
    {
    	stdid = result.getString("stdid");
    	SelectID = result.getString("id");
    	SelectPW = result.getString("passwd");
    	Name = result.getString("name");
    	signcheck = result.getString("signcheck");
    }
    
    // 에러 처리
	}catch(SQLException ex){
	    ex.printStackTrace();
	}finally{
	    if(pstmt !=null)
	        try{pstmt.close();}catch(SQLException sqle){}

	    if(conn !=null)
	        try{conn.close();}catch(SQLException sqle){}
	}

    // 로그인 결과 처리 ( 로그인 성공시 세션 처리 )
    if (id.equals(MasterID) && pw.equals(MasterPW)) // 관리자 로그인시
    {
    	session.setAttribute("MLoginID", MasterID);   // 로그인 성공을 나타내는 특정 속성 설정
        session.setAttribute("MName" , MasterName);
%>
<script>
	alert("관리자로 로그인 되었습니다.");
	location.href="main.jsp";
</script>
<%
    }
    else if(id.equals(SelectID) && pw.equals(SelectPW) && signcheck.equals(sign)) //아이디와 패스워드 모두 일치
    {  
     	session.setAttribute("LoginID", id);   // 로그인 성공을 나타내는 특정 속성 설정
     	session.setAttribute("Name" , Name);
     	session.setAttribute("StdID", stdid);
%>
<script>
	alert("로그인 되었습니다.");
	location.href="main.jsp";
</script>
<%
	} 
    else if (id.equals(SelectID) && pw.equals(SelectPW))
	{
%>
<script>
	alert("승인 되지 않은 사용자입니다.");
	location.href="main.jsp";
</script>
<%
	}
	else if (id.equals(SelectID)){
%>
<script>
alert("패스워드가 다릅니다.");
history.go(-1);
</script>
<%
	}else {
%>
<script>
alert("존재하지 않는 ID입니다.");
history.go(-1);
</script>
<%
}
%>