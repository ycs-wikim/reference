<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<link rel="stylesheet" href="css/bootstrap.css" />
<jsp:include page = "top.jsp" flush = "false"/>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Login Page</title>
 <script type="text/javascript">
    
        function checkValue()
        {
            inputForm = eval("document.loginInfo");
            if(!inputForm.id.value)
            {
                alert("아이디를 입력하세요");    
                inputForm.id.focus();
                return false;
            }
            if(!inputForm.pw.value)
            {
                alert("비밀번호를 입력하세요");    
                inputForm.pw.focus();
                return false;
            }
        }
    
    </script>
</head>
<body>

	<section id="footer">
		<div class="container">
			<header class="major">
				<h2>로그인</h2>
			</header>
			<form action="loginOK.jsp" method="post"  onsubmit="return checkValue()" name="loginInfo">
				<div class="row gtr-uniform">
					<h4>ID</h4>
					<div class="col-12">
						<input type="text" name="id"
							value="<%if (session.getAttribute("id") != null)
				out.println(session.getAttribute("id"));%>"
							placeholder="ID" />
					</div>
					<h4>PW</h4>
					<div class="col-12">
						<input type="password" name="pw" placeholder="PW" />
					</div>
					<div class="col-12">
						<ul class="actions special">
							<li><input type="submit" value="로그인" class="primary" /></li>
							<li><input type="button" value="회원가입" class="primary"
								onclick="javascript:window.location='join.jsp'"></li>
						</ul>
					</div>
				</div>
			</form>
			</div>
	</section>

</body>
</html>