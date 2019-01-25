/**
 * @file echo_client.c
 * @author pplovelyliu
 * @brief 回声客户端
 * @version 0.1
 * @date 2018-11-23
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    //这是什么头文件？
#include <arpa/inet.h> //这是干什么的？地址解析吗？
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;                     //本地电话机
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_addr; //服务器电话机地址ip和port

    if (argc != 3)
    {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    //创建本地电话
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    //用本地电话机给对方电话号码打电话
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("connect() error");
    }
    
    else
    {
        puts("Connected……");
    }

    while(1)
    {
        //写之前先清空
        memset(message, 0, BUF_SIZE);

        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
            break;
        }

        write(sock, message, strlen(message));

        //读之前先清空
        memset(message, 0, BUF_SIZE);

        str_len = read(sock, message, BUF_SIZE-1);
        message[str_len] = 0;
        printf("Message, from server: %s", message);
    }
    close(sock);
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
 * gcc echo_client.c -o eclient
 * 
 */