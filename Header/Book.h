/*
 * @Descripttion: Book类 .h头文件
 * @Author: Hx
 * @Date: 2021-12-12 23:08:25
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-21 22:09:42
 */
#ifndef BOOK_H_INCLUDE
#define BOOK_H_INCLUDE

#include"Common.h"

typedef struct book{
    KeyType ISBN;   //书的编号
    char *name;     //书名
    char *Author;   //作者
    char *classification; //书的类型
    int count;  //书的库存数
    int Lent;   //借出数量
}book, *Book;

#endif //BOOK_H_INCLUDE