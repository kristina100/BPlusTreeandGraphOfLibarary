/*
 * @Descripttion: Book类 .h头文件
 * @Author: Hx
 * @Date: 2021-12-12 23:08:25
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 15:11:27
 */
#ifndef BOOK_H_INCLUDE
#define BOOK_H_INCLUDE

#include"Common.h"

typedef struct book{
    int ISBN;   //书的编号
    char *Title; //书名
    char *Author;   //作者
    char *press;    //出版社
    char *publishing_year;  //出版时间 
    char *classification; //书的类型
    float price;    //价格
    Status status;  //状态
}book, *Book;

/**
 * @brief 输入书本信息
 * 
 * @return Book 
 */
Status inputBookInfo(Book &book);



#endif //BOOK_H_INCLUDE