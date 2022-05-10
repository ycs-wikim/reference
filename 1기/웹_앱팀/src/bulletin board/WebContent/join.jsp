<%@page import="java.io.PrintWriter"%>
<link rel="stylesheet" href="css/bootstrap.css" />
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<jsp:include page = "top.jsp" flush = "false"/>
    
<html>
<head>
<meta charset="UTF-8">

    <title>회원가입 화면</title>
    <script type="text/javascript">
    
        // 필수 입력정보인 아이디, 비밀번호가 입력되었는지 확인하는 함수
        function checkValue()
        {
            if(!document.userInfo.id.value){
                alert("아이디를 입력하세요.");
                return false;
            }
            
            if(!document.userInfo.pw.value){
                alert("비밀번호를 입력하세요.");
                return false;
            }
            
            // 비밀번호와 비밀번호 확인에 입력된 값이 동일한지 확인
            if(document.userInfo.pw.value != document.userInfo.pw_check.value ){
                alert("비밀번호를 동일하게 입력하세요.");
                return false;
            }
        }
      
    </script>
    
</head>
<body>

<section id=footer>
		<div class="container">
			<header class="major">
				<h2>회원가입</h2>
			</header>
			<form action="joinOK.jsp" method="post" name="userInfo" onsubmit="return checkValue()">
				<div class="row gtr-uniform">
					<div class="col-12">
						<input type="text" name="id" placeholder="아이디" />
					</div>
					<div class="col-12">
						<input type="password" name="pw" placeholder="비밀번호" />
					</div>
					<div class="col-12">
						<input type="password" name="pw_check" placeholder="비밀번호 재확인" />
					</div>
					<div class="col-12">
						<input type="text" name="name" placeholder="이름" />
					</div>
					<div class="col-12">
						<input type="text" name="stdID" placeholder="학번" />
					</div>
						<div class="col-12">
						 <input type="text" name="userEmail" placeholder="이메일@naver.com" maxlength="20">
					</div>
					<div class="col-12">
						<ul class="actions special">
							<li><input type="submit" value="회원가입"
								onclick="infoConfirm()" class="primary"></li>
							<li><input type="reset" value="취소"
								onclick="javascript:window.location = 'main.jsp'"
								class="primary"></li>
						</ul>
					</div>
				</div>
			</form>
	</section>
</html>
