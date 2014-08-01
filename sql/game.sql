DROP TABLE IF EXISTS player_account;
CREATE TABLE player_account (
	p_account varchar(32) NOT NULL PRIMARY KEY,
	p_password varchar(32) NOT NULL
);

DROP TABLE IF EXISTS role_info;
CREATE TABLE role_info (
	r_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	r_account varchar(32) NOT NULL,
	r_name varchar(32) NOT NULL,
	r_an_type INT NOT NULL,
	r_hp INT NOT NULL,
	r_map_id INT NOT NULL,
	r_x INT NOT NULL,
	r_y INT NOT NULL
);



INSERT INTO player_account VALUES('zhao' , 'zhao');
INSERT INTO role_info	   VALUES(1 , 'zhao' , 'carma' , 0 , 100 , 26 , 50 , 50);
INSERT INTO player_account VALUES('black' , 'black');
INSERT INTO role_info(r_account , r_name , r_an_type , r_hp , r_map_id , r_x , r_y)	   VALUES('black' , 'machine' , 0 , 100 , 26 , 110 , 100);
INSERT INTO player_account VALUES('xin' , 'xin');
INSERT INTO role_info(r_account , r_name , r_an_type , r_hp , r_map_id , r_x , r_y)	   VALUES('xin' , 'xinge' , 0 , 100 , 26 , 110 , 50);
INSERT INTO player_account VALUES('quan' , 'quan');
INSERT INTO role_info(r_account , r_name , r_an_type , r_hp , r_map_id , r_x , r_y)	   VALUES('quan' , 'xiaoquan' , 0 , 100 , 26 , 110 , 150);
