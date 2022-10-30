#ifndef MYSQL_CLIENT_MYSQL_H
#define MYSQL_CLIENT_MYSQL_H

#endif //MYSQL_CLIENT_MYSQL_H
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