create table member(
	stdid int primary key,
	id varchar(20) not null,
	passwd varchar(30) not null,
	name varchar(20) not null,
	email varchar(50) not null,
	signcheck varchar(5) not null CHECK(signcheck IN('X', 'O')),
	sign_date datetime not null
) charset = 'utf8';

create table board(
	boardid int AUTO_INCREMENT primary key,
	title varchar(50) not null,
	boardtype varchar(30) not null,
	writer varchar(50),
	wrdate datetime,
	wrcontent varchar(500) NOT NULL
) charset = 'utf8';
 
update member set signcheck = 'O' where id = 'geun10121';

drop table member;