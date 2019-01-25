/**
 * @file echo_server.c
 * @author your name (you@domain.com)
 * @brief  回声服务端
 * @version 0.1
 * @date 2018-11-23
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
    }

    clnt_adr_sz = sizeof(clnt_adr);
    int i;
    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

        if (clnt_sock == -1)
        {
            error_handling("accept() error");
        }
        else
        {
            printf("Connected client %d \n", i + 1);
        }

        //下一个用户进来之前先清空
        memset(message, 0, BUF_SIZE);
        
        while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
        {
            printf("Message from client %s \n", message);
            write(clnt_sock, message, str_len);

            //写完之后也要清空，不然循环读的时候这里面还有脏数据
            memset(message, 0, BUF_SIZE);
        }

        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/**
 * @brief 生成可执行文件
 * 
 * gcc echo_server.c -o eserver
 * 
 */