/**
 * @file inet_addr.c
 * @author pplovelyliu
 * @brief IP字符串转为网络字节序的32位整型数据
 * @version 0.1
 * @date 2018-11-18
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256"; //此处故意弄一个错误的ip。1个字节8位，取值范围是0-255

    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
    {
        printf("Error occured! \n");
    }
    else
    {
        printf("Network ordered integer addr: %#lx \n", conv_addr);
    }

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
    {
        printf("Error occured! \n");
    }
    else
    {
        printf("Network ordered integer addr: %#lx \n", conv_addr);
    }

    return 0;
}

/**
 * @brief 生成可执行文件
 * 
 * gcc inet_addr.c -o addr
 * 
 */