/**
 * @file hello_server.c
 * @author pplovelyliu
 * @brief  第一个服务器程序
 * @version 0.1
 * @date 2018-11-17
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

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock; //服务器socket，类比为服务器电话机
    int clnt_sock; //客户端socket，类比为用户的电话机

    struct sockaddr_in serv_addr; //socket地址，分配ip和端口的吧
    struct sockaddr_in clnt_addr;

    socklen_t clt_addr_size; //地址长度

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    //创建服务器socket,返回socket文件描述符
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    //判断是否正常创建
    if (serv_sock == -1)
    {
        error_handling("socket() error");
    }

    //给serv_addr分配内存
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    //分配一个电话号码给电话机
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("bind() error");
    }

    //给电话连线
    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
    }

    clt_addr_size = sizeof(clnt_addr);
    //接听电话，返回对方的电话机信息和号码信息
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clt_addr_size);

    if (clnt_sock == -1)
    {
        error_handling("accept() error");
    }

    //跟对方聊天 “hello world”
    write(clnt_sock, message, sizeof(message));

    //聊天完成之后需要挂掉电话
    close(clnt_sock);
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
 * @brief int socket(int domain, int type, int protocol); 
 * 
 * domain：     协议族信息
 * type：       套接字传输类型信息
 * protocol：   计算机间通信中使用的协议信息
 * 
 */

/**
 * @brief 协议族， 在头文件 sys/socket.h 中定义
 * 
 * PF_INET	  IPv4互联网协议族
 * PF_INET6   IPV6互联网协议族
 * PF_LOCAL   本地通信的UNIX协议族
 * PF_PACKET  底层套接字协议族
 * PF_IPX	  IPX Novell协议族
 * 
 */

/**
 * @brief 套接字类型， 指套接字的数据传输方式
 * 
 * SOCK_STREAM      面向连接的套接字，特点：1. 数据不会消失(可靠的) 2. 按序传递 3. 不存在数据边界(socket内部有字节数组缓冲区)
 * SOCK_DGRAM	    面向消息的套接字，特点：1. 不可靠的 2. 不按序传递的 3. 以数据的高速传递为目的
 * 
 */

/**
 * @brief 协议类型,这个很好理解
 * 
 * IPPROTO_TCP
 * OPPROTO_UDP
 * 
 */

/**
 * @brief 网络地址。为使计算机连接到网络并收发数据，必须向其分配IP地址
 * 
 * IPv4(Internet Protocol version 4)    4字节地址族
 * IPv6(Internet Protocol version 6)    16字节地址族
 * 
 */

/**
 * @brief IPv4标准4字节IP地址分为网络地址和主机地址，主要是为了区分不同的网络
 * 
 * A    网络id占1字节，主机id占3字节
 * B    网络id占2字节，主机id占2字节
 * C    网络id占3字节，主机id占1字节
 * D    网络id占4字节
 * E    已经被预约的地址
 * 
 * 数据传输过程：先通过网络地址将数据传输到该网络，再通过主机id找到该网络下的具体设备
 * 
 */

/**
 * @brief 网络地址分类与主机地址边界
 * 
 * 根据IP地址的第一个字节即可判断网络地址占用的字节书
 * A类地址的首字节范围： 0-127
 * B类地址的首字节范围： 128-191
 * C类地址的首字节范围： 191-223
 * 
 * 或者如下表示
 * 
 * A类地址的首位以0开始
 * B类地址的前2位以10开始
 * C类地址的前3位以110开始
 * 
 */

/**
 * @brief 用于区分套接字的端口号
 * 
 * 由IP能够找到目标主机设备，但是数据要传输给哪个应用(socket)呢？这就是端口号来确定的
 * 
 */

/*
 * @brief 地址信息的表示
 
struct sockaddr_in {
	__uint8_t	sin_len;
	sa_family_t	sin_family;
	in_port_t	sin_port;
	struct	in_addr sin_addr;
	char		sin_zero[8];
};

struct in_addr {
	in_addr_t s_addr;
}; 

typedef	unsigned short		__uint16_t;
typedef	__uint16_t		    in_port_t;

重新定义的数据类型，主要是考虑扩展性。比如in_port_t 不管在哪个平台上都能是16位

*/

/**
 * @brief 网络字节序保存端口号和IP地址
 * 
 * 因为不同的CPU中，内存空间存储的字节顺序不一样，这就导致接收到的数据解析时发生错误
 * 
 * 
 * 字节序(Order) 与 网络字节序
 * 
 * 大端序： 高位字节存放在低位地址   
 * 小端序： 高位字节存放在高位地址
 * 注意： 这里的低位地址和高位地址，是相当于数组的0位置的。0就是最低， 另外一端就是最高
 * 
 * 网络字节序是数据传输双方约定好的，很简单，统一为大端序
 * 
 */

/**
 * @brief 字节序转换
 * 
 * unsigned short htons(unsigned short)
 * unsigned short ntohs(unsigned short)
 * unsigned short htonl(unsigned long)
 * unsigned short ntohl(unsigned long)
 * 
 * htons中的h表示主机(host)字节序
 * htons中的n表示网络(network)字节序
 * s 指short ，l指long(Linux中long类型占用4个字节)
 */

/**
 * @brief IP字符串转32位网络字节序的整型
 * 
 * in_addr_t inet_addr(const char *string)
 * 
 */