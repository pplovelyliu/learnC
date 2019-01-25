/**
 * @file endian_conv.c
 * @author pplovelyliu
 * @brief 主机字节序和网络字节序的转换
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
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port: %#x \n", host_port);
    printf("Network ordered port: %#x \n", net_port);

    printf("Host ordered address: %#x \n", host_addr);
    printf("Network ordered address: %#x \n", net_addr);

    return 0;
}

/**
 * @brief 生成可执行文件
 * 
 * gcc endian_conv.c -o conv
 * 
 */
