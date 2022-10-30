# C-_mysql_client
C++下的mysql客户端开发

先展示一下效果图
下图是正宗的mysql：

<img width="588" alt="image" src="https://user-images.githubusercontent.com/77431730/198860488-62d1ad0d-cf6c-41f8-9db8-e736d13460ac.png">

下图是我利用Mysql API函数，实现一个类Mysql的客户端窗口：

<img width="587" alt="image" src="https://user-images.githubusercontent.com/77431730/198860577-de15b2c1-2fdd-4369-bd37-7cc02ed4f62b.png">

可以看出来和原版效果差不多吧～，下面来和我一起学习吧！

## 案例分析
需求：在C++下，利用Mysql API函数，实现一个类Mysql的客户端窗口，实现对mysql数据库的操作

它是个什么项目？——在C++下利用Mysql API实现Mysql的功能的类Mysql的客户端，助力初学者快速熟悉Mysql命令以及Mysql API

## 整体流程
流程是用C写的，和C++用类实现大差不差，主要看看整体流程的逻辑
```
mysql客户端编写思路分析:
1 mysql初始化--mysql_init
2 连接mysql数据库---mysql_real_connect
3 while(1)
  {
  	//打印提示符:write(STDOUT_FILENO, "mysql >", strlen("mysql >"));
  	//读取用户输入: read(STDIN_FILENO, buf, sizeof(buf))
  	//判断用户输入的是否为退出: QUIT quit exit EXIT
  	if(strncasecmp(buf, "exit", 4)==0 || strncasecmp(buf, "quit", 4)==0)
  	{
  		//关闭连接---mysql_close();
  		exit();
  	}
  	
  	//执行sql语句--mysql_query();
  	
  	//若不是select查询, 打印执行sql语句影响的行数--mysql_affected_rows();
  	if(strncasecmp(buf, "select", 6)!=0)
  	{
  		printf("Query OK, %d row affected", mysql_affected_rows());
  		continue;
  	}
  	
  	//若是select查询的情况
  		---//获取列数: mysql_field_count()
  	//获取结果集: mysql_store_result()
  		--获取列数: int mysql_num_fields();
  	//获取表头信息并打印表头信息:mysql_fetch_fields();
  		
  	//循环获取每一行记录并打印: mysql_fetch_row()
  	//释放结果集: mysql_free_result()
  	
  }
  
4 关闭连接: mysql_close();
```

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
