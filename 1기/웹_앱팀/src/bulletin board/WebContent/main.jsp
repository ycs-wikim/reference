<%@page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<%-- 
<% session.getAttribute("StdID"); %>
<% session.getAttribute("Name"); %>
<% session.getAttribute("LoginID"); %> --%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>main</title>
<link href="css/main.css" type="text/css" rel = "stylesheet">
<style>

</style>
</head>
<body>
<!-- top 레이아웃 include -->
<jsp:include page = "top.jsp" flush = "false"/>
<br><br>

<!-- 전체적인 배치 : { [ 프로필 , 카테고리 ] , [ 공지사항 , 최근 게시글 ] } -->
<div class="mainbatch1">
		<jsp:include page = "info.jsp" flush = "false"/>
		<!--<jsp:include page = "category.jsp" flush = "false"/>-->
<!-- notice와 newpost를 세로로 정렬하기 위한 table 적용 -->
<table>
	<tr><td><jsp:include page = "notice.jsp" flush = "false"/></td></tr>
	<tr><td><jsp:include page = "newpost.jsp" flush = "false"/></td></tr>
</table>	
</div>

</body>
</html>


