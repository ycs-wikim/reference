//script.js 

$(document).ready(function(){ 
	//menu v2 
	$(".menu-v2").mouseover(function(){
	 $(this).children(".submenu").show(200);
	}); 
	
	$(".menu-v2").mouseleave(function(){ 
	$(this).children(".submenu").hide(200); 
	}); 
});

