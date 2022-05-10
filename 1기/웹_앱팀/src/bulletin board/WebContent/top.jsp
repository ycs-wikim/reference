<%@ page language="java" contentType="text/html; charset=UTF-8"
   pageEncoding="UTF-8"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<style>
/* 배경 워터마크의 크기와 위치 조정 */
body{
background-image: url('bg_yuhanlogo.png');
background-attachment: fixed;
background-repeat: no-repeat;
background-position: 60% 40%;
}

</style>
<meta name="viewport"
   content="width=device-width, initial-scale=1, shrink-to-fit=no">
<title>레퍼런스 웹/앱팀</title>
<link rel="stylesheet"
   href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">

</head>

<!-- 네비바를 fiexd-top으로 설정했을 때 컨텐츠와 겹치는 문제 방지 -->
<body class="pt-5">

   <!-- Navigation -->
   <nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top">
      <div class="container">
         <img src="bn_reflogo.png" width=150px; height=40px;>
         <div class="collapse navbar-collapse" id="navbarResponsive">
            <ul class="navbar-nav ml-auto">
               <li class="nav-item active"><a class="nav-link" href="main.jsp">홈
                     <span class="sr-only">(current)</span>
               </a></li>
            <% 
            String master = (String)session.getAttribute("MLoginID");
            String student = (String)session.getAttribute("LoginID");
            //	로그인을 하지 않은 상태
            if(master==null && student==null)
            {
            %>
               <li class="nav-item"><a class="nav-link"
                  href="login.jsp">로그인</a></li>
               <li class="nav-item"><a class="nav-link"
                  href="join.jsp">회원가입</a></li>
            <%
            }
            %>
            </ul>
         </div>
      </div>
   </nav>
   