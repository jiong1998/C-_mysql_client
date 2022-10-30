# C-_mysql_client
C++下的mysql客户端开发

先展示一下效果图


需求：在C++下，利用Mysql API函数，实现一个类Mysql的客户端窗口，实现对mysql数据库的操作

它是个什么项目？——在C++下利用Mysql API实现Mysql的功能的类Mysql的客户端，助力初学者快速熟悉Mysql命令以及Mysql API

## 代码分析：
主要实现CRUD操作，增删改操作不需要额外处理，所以可以放一起操作，而查由于需要获取结果集，所以需要单独处理。

主要实现的功能如下：
```cpp
class Mysql
{
public:
    //初始化数据库，连接数据库
    Mysql(char* ip, char* user, char* password, char* db, int port);

    //增删改操作----update\insert\delete
    void db_CUD(char * buf);

    //查操作----select
    void db_select(char * buf);

    //判断是什么语句，然后自动调用相应的操作
    void execute_sql(char * buf);

    //断开数据库的连接
    void db_close();

    MYSQL * m_mysql;
    MYSQL * m_conn;
    MYSQL_RES * m_result;
};

```

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
