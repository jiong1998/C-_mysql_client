# C-_mysql_client
C++下的mysql客户端开发

需求：在C++下，利用Mysql API函数，实现一个类Mysql的客户端窗口，实现对mysql数据库的操作

```
输出结果
before:utf8mb4
after:utf8mb3
mysql> select * from score
+----+-----------+------+--------------------+--------+------------+-----------+---------+
id	name	math	english	chinese	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
1	Tom	67	88	95	
2	Rose	23	66	90	
3	Jack	56	98	76	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
mysql> insert into score values (4, "lu", 23, 42, 55)                       
Query OK, 1 rows affected
Rows matched: 1  Changed: 1  Warnings: 0
mysql> select * from score
+----+-----------+------+--------------------+--------+------------+-----------+---------+
id	name	math	english	chinese	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
1	Tom	67	88	95	
2	Rose	23	66	90	
3	Jack	56	98	76	
4	lu	23	42	55	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
mysql> delete from score where id=4
Query OK, 1 rows affected
Rows matched: 1  Changed: 1  Warnings: 0
mysql> select * from score
+----+-----------+------+--------------------+--------+------------+-----------+---------+
id	name	math	english	chinese	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
1	Tom	67	88	95	
2	Rose	23	66	90	
3	Jack	56	98	76	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
mysql> update score set math = 33 where id = 3
Query OK, 1 rows affected
Rows matched: 1  Changed: 1  Warnings: 0
mysql> select * from score
+----+-----------+------+--------------------+--------+------------+-----------+---------+
id	name	math	english	chinese	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
1	Tom	67	88	95	
2	Rose	23	66	90	
3	Jack	33	98	76	
+----+-----------+------+--------------------+--------+------------+-----------+---------+
mysql> error
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near'error
'at line 1
mysql> quit
Bye
