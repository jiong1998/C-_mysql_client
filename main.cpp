//C++实现mysql客户端开发
#include <iostream>
#include <mysql.h>
#include <string>
#include <unistd.h>
#include "Mysql.h"
using namespace std;


//处理buf异常情况
int clean_buf(char * buf)
{
    //处理输入回车报错的情况
    if(buf[0]=='\n')
        return 1;

    //去掉末尾的;
    char * p = strrchr(buf, ';');
    if(p!=NULL)
        *p = 0x00;

    //去除前面的空格
    int i;
    for(i=0; strlen(buf);++i)
    {
        if(buf[i]!=' ')//只要前面是空格，指针往前走
            break;
    }
    int n = strlen(buf);
    memmove(buf, buf+i, n-i+1);//memmove拷贝字符串。+1是因为多拷贝一个\0

    return 0;
}

int main()
{
    char buf[1024];
    //初始化、连接数据库
    Mysql mysql=Mysql("localhost", "root", "Aa82981388", "heima", 0);
    while(1)
    {
        //将"mysql"输出到终端
        write(STDIN_FILENO,"mysql> ",strlen("mysql> "));

        //获取用户输入
        memset(buf,0x00,sizeof(buf));
        read(STDOUT_FILENO, buf, sizeof(buf));

        //处理buf异常情况
        int flag = clean_buf(buf);
        if(flag==1)
            continue;

        //判断是什么语句,然后自动执行相应的语句
        mysql.execute_sql(buf);
    }
}
