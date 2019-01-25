/**
 * @file inet_aton.c
 * @author pplovelyliu
 * @brief 与inet_addr.c功能一样的，只是接口名不同而已
 * @version 0.1
 * @date 2018-11-18
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(void)
{
    char *addr = "123.232.124.79";
    struct sockaddr_in addr_inet;

    //正常转换返回1， 错误返回0
    if (!inet_aton(addr, &addr_inet.sin_addr))
    {
        error_handling("Conversion error");
    }
    else
    {
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
    }

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
 * gcc inet_aton.c -o aton
 * 
 */