/**
 * @file FuncPointer.c
 * @author pplovelyliu
 * @brief  函数指针
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>

void print()
{
    printf ( "this is a function pointer, and has no params\n" );
}

void print2(char* msg)
{
    printf ( msg );
}

int main(int argc, char *argv[])
{
    void (*fp)() = print;
    (*fp)();

    char* msg = "this is a func pointer, and the function has a params\n";
    void (*fp2)(char*) = print2;
    (*fp2)(msg);
}