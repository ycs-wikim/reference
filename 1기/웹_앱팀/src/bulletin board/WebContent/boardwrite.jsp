<%@ page language="java" contentType="text/html; charset=UTF-8"
   pageEncoding="UTF-8"%>
<% request.setCharacterEncoding("UTF-8"); %>

   <%@page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<link href="css/boardwrite_css.css" type="text/css" rel = "stylesheet">

<title>게시글 작성</title>
</head>

<script type="text/javascript">
   function ContentCheck(){
      inputForm = eval("document.write");
      
      if(inputForm.kind.value == "none"){
         alert("게시판을 선택하세요");
         inputForm.kind.focus();
         return false;
      }
      if(!inputForm.title.value){
         alert("제목을 입력하세요");
         inputForm.title.focus();
         return false;
      }
      if(!inputForm.content.value){
         alert("내용을 입력하세요");
         inputForm.content.focus();
         return false;
      }
   }
</script>

<body class="pt-5">

<%
String name = (String)session.getAttribute("Name");  //로그인한 사람의 이름
String manager = (String)session.getAttribute("MName");  //관리자의 이름
String id = request.getParameter("title");  //modify.jsp에서 글 수정버튼 누를 때 현재 게시글의 boardid값
String kind = request.getParameter("kind");  //게시판 종류
String board_name="";

switch(kind){

case "web" :
   board_name = "웹/앱";
   break;
case "ai" :
   board_name = "인공지능";
   break;
case "net" :
   board_name = "네트워크";
   break;
case "game" :
   board_name = "게임";
   break;
case "daily" :
   board_name = "일상";
   break;
case "notice" :
	board_name = "공지사항";
	break;
}

int i_id;

if(id == null)
   i_id = 0;
else
   i_id = Integer.parseInt(id);

String b_title = null;
String b_content = null;
String b_num = null;

if(name == null && manager == null){
   %>
<script>
   alert("로그인 후 이용 가능합니다.");
   location.href = "login.jsp";
</script>
<%} %>
<!-- Navigation -->
<jsp:include page = "top.jsp" flush = "false"/>      
      <br>
<form action="writeOK.jsp?kind=<%=kind%>" method="post" onsubmit="return ContentCheck()" name="write">

   <fieldset>
   <div class = "board_position">
   <h3>&nbsp;게시글 작성</h3>
   <%
   if(i_id == 0){
   %>
   <table class="table">
   <tr><th colspan="2" style="text-align:center"><%=board_name%></th></tr>
   <tr><th>제목</th>
   <th><textarea class = "title" id = "title" name = "title" placeholder= "제목을 입력해주세요." cols = "100" ></textarea>
</th></tr>
    <tr><td>내용</td><td><textarea  placeholder="내용을 입력하세요." name = "content" cols = "60" rows = "20" ></textarea></td></tr>
  </table>
  
  <%
   }else{
   
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
         String sql = "select boardid, title, wrcontent from board where boardid=?";
         pstmt = conn.prepareStatement(sql);
         pstmt.setInt(1, i_id);
         rs = pstmt.executeQuery();
         
         //각각의 결과 레코드를 변수에 입력
         while(rs.next()){
            b_title = rs.getString("title");
            b_content = rs.getString("wrcontent");
            b_num = rs.getString("boardid");
         }
   
   %>
   <table class="table">
   <tr><th colspan="2" style="text-align:center"><%=board_name%></th></tr>
   <tr><th>제목</th><th><textarea class = "title" id = "title" name = "title" rows= "1"><%=b_title%></textarea>
</th></tr>
   
    <tr><td>내용</td><td><textarea name = "content" rows = "20" ><%=b_content%></textarea></td></tr>
  </table> 
 	<input type="hidden" value="1" name="update">
   <input type="hidden" value="<%=i_id%>" name="id">
  
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
   <div class = "button_location">
   <button type="submit" class="btnB">게시글 작성</button>
   <button type="button" class="btnB" onclick="javascript:history.back()">취소</button>&nbsp;
    </div>
    </div>
  </fieldset>
   </form>
</body>
</html>