<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<% request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="css/category.css" />
<link href="css/table.css" type="text/css" rel = "stylesheet">
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>

	<div class="col-lg-3">

        <ul class="mainMenu">
        	 <li class="item">
                <a href="AI.jsp?kind=notice" class="btnC"><i class="fas fa-sign-out-alt"></i>공지사항</a>
            </li>
        
        	 <li class="item" id="about">
                <a href="AI.jsp?kind=daily" class="btnC"><i class="fas fa-address-card"></i>일상 게시판</a>
                
            </li>
           
           
            <li class="item" id="account">
          
                <a href="#account" class="btnC"><i class="fas fa-user-circle"></i>코드 공유</a>
                <div class="subMenu">
                    <a href="AI.jsp?kind=web">웹/앱</a>
                    <a href="AI.jsp?kind=game">게임</a>
                    <a href="AI.jsp?kind=ai">인공지능</a>
                    <a href="AI.jsp?kind=net">네트워크</a>
                </div>
            </li>
        </ul>
    </div>
</body>
</html>