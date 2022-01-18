#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")   //连接入ws_32.lib库
#else
//#include <sys/socket.h>
//#include <apra/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#endif
#if 0

#include <stdio.h>
#include "sqlite3.h"


int create_sqlite_db(char* name)
{
    int ret = -1;
    sqlite3 *db = NULL;
    char *sql = NULL;
    ret = sqlite3_open(name, &db);

    sql = "create table map(id int primary key, x int, y int)";
    sqlite3_exec(db, sql, NULL, NULL, NULL);
    sql = "insert into map values(1001, 1000, 1000)";
    sqlite3_exec(db, sql, NULL, NULL, NULL);
    sqlite3_close(db);
    return 0;
}


int sockaddr_info()
{
    int rc = 0;
    char host_name[128] = {0};
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    struct addrinfo *ap = NULL;
    struct sockaddr_in *addr;
    gethostname(host_name, sizeof(host_name));
     printf("hostname %s\n", host_name);
    //rc = getaddrinfo(host_name, NULL, NULL, &res);
    rc = getaddrinfo(NULL, "8988", NULL, &res);
    if (res)
    {
        for(ap = res; ap != NULL; ap = ap->ai_next)
        {
            if(ap->ai_family == AF_INET)
            {

                addr = (struct sockaddr_in*)ap->ai_addr;
                if (NULL == addr)
                {
                    printf("##111\n");

                }
                else
                {
                    printf("local ip:%s\n", inet_ntoa(addr->sin_addr));
                }
               
            }
  
        }

        
    }
    freeaddrinfo(res);
    return rc;
}


#endif


int main()
{
    int rc = 0;
    //rc = sockaddr_info();    
    unsigned char command = (1<<1);
    printf("##2# %u\n", command);
    return 0;
}










