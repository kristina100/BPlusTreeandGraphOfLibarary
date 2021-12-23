/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-22 14:28:23
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-22 20:12:02
 */
#include"../Header/Book.h"
#include"string.h"

/**
 * @brief 输入书本信息
 */
Status inputBookInfo(Book &b)
{

    b = (Book)malloc(sizeof(book));
    if(b == NULL)   return OVERFLOW;

    char *author = NULL, *cf = NULL, *name = NULL;
    author = (char*)malloc(sizeof(char)*20);
    cf = (char*)malloc(sizeof(char)*20);
    name = (char*)malloc(sizeof(char)*20);

    //输入书名
    printf("please input Title:");
    scanf("%s", name);

    //输入IBSN
    printf("please input ISBN:");
    scanf("%d", &b->ISBN);

    //输入作者
    printf("please input Author:");
    scanf("%s", author);

    //输入类别
    printf("please input Classification:");
    scanf("%s", cf);
    
    //根据输入的字长分配空间之后赋给b
    b->classification = (char*)malloc(sizeof(char) * strlen(cf));
    b->Author = (char*)malloc(sizeof(char) * strlen(author));
    b->Title = (char*)malloc(sizeof(char) * strlen(name));
    strcpy(b->Title, name);
    strcpy(b->Author, author);
    strcpy(b->classification, cf);
    return SUCCESS;
}