#include "Mysql.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <unistd.h>

Mysql::Mysql(char* ip, char* user, char* password, char* db, int port)
{
    //初始化数据库
    this->m_mysql = mysql_init(NULL);
    if(this->m_mysql == NULL)
    {
        printf("mysql init error \n");
        exit(-1);
    }

    //连接数据库
    this->m_conn = mysql_real_connect(this->m_mysql, ip, user, password, db, port, NULL, 0);
    if(this->m_conn==NULL)
    {
        printf("mysql connect error ! \n");
        exit(-1);
    }

    //设置字符集----解决中文问题
    cout<<"before:"<<mysql_character_set_name(this->m_conn)<<endl;
    mysql_set_character_set(this->m_conn,"utf8");//设置字符集为 utf8
    cout<<"after:"<<mysql_character_set_name(this->m_conn)<<endl;

}

//增删改操作----update\insert\delete
void Mysql::db_CUD(char * buf)
{
    int ret = mysql_query(this->m_conn, buf);

    //通过调用mysql_affected_rows()，可发现有多少行已被改变（影响）。
    if( ret == 0)//mysql_query调用成功
    {
        ret = mysql_affected_rows(this->m_conn);
        cout<<"Query OK, "<< ret <<" rows affected"<<endl;
        cout<<"Rows matched: "<<ret<<"  Changed: "<<ret<<"  Warnings: 0"<<endl;
    }
    else//mysql_query调用失败---sql语句出错
        cout<<"ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '' at line 1"<<endl;
}

//查操作----select
void Mysql::db_select(char *buf)
{
    int ret = mysql_query(this->m_conn, buf);
    if(ret != 0)
        cout<<"mysql_query--select失败！"<<endl;
    else
    {
        //获取数据集
        this->m_result = mysql_store_result(this->m_conn);

        //获取失败
        if( this->m_result == NULL)
        {
            cout<<"mysql_store_result error";
            return;
        }

            //获取成功
        else
        {
            //获取列数
            int row_num = mysql_num_fields(this->m_result);

            //打印表头信息
            MYSQL_FIELD *fields = NULL;
            fields = mysql_fetch_fields(this->m_result);	//得到表头的结构体数组
            cout<<"+----+-----------+------+--------------------+--------+------------+-----------+---------+"<<endl;
            for(int i=0; i<row_num; ++i)
            {
                cout<<fields[i].name<<"\t";
            }
            cout<<endl;
            cout<<"+----+-----------+------+--------------------+--------+------------+-----------+---------+"<<endl;

            //获取结果集每一行记录
            MYSQL_ROW row;
            while( row = mysql_fetch_row(this->m_result) )
            {
                for (int i=0; i<row_num; i++)
                {
                    cout<<row[i]<<"\t";
                }
                cout<<endl;
            }
            cout<<"+----+-----------+------+--------------------+--------+------------+-----------+---------+"<<endl;

            //释放结果集
            mysql_free_result(this->m_result);
        }
    }

}

//判断是什么语句，然后自动调用相应的操作
void Mysql::execute_sql(char * buf)
{
    //先判断是不是QUIT quit EXIT exit
    if(strncasecmp(buf, "quit", 4)==0 || strncasecmp(buf, "exit", 4) == 0)
    {
        this->db_close();
    }

        //在判断是增删改还是查
    else if( strncasecmp(buf, "insert", 6) == 0 || strncasecmp(buf, "update", 6) == 0 || strncasecmp(buf, "delete", 6) == 0)
    {
        db_CUD(buf);
    }

    else if(strncasecmp(buf, "select", 6) == 0)
    {
        db_select(buf);
    }

        //输入错误指令
    else
    {
        cout<<"ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near"<<"\'"<<buf<<"\'at line 1"<<endl;
    }

}

//关闭连接
void Mysql::db_close()
{
    mysql_close(this->m_conn);
    cout<<"Bye"<<endl;
    exit(1);
}
