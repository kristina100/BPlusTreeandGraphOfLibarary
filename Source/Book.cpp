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
 * @brief �����鱾��Ϣ
 */
Status inputBookInfo(Book &b)
{

    b = (Book)malloc(sizeof(book));
    if(b == NULL)   return OVERFLOW;

    char *author = NULL, *cf = NULL, *name = NULL;
    author = (char*)malloc(sizeof(char)*20);
    cf = (char*)malloc(sizeof(char)*20);
    name = (char*)malloc(sizeof(char)*20);

    //��������
    printf("please input Title:");
    scanf("%s", name);

    //����IBSN
    printf("please input ISBN:");
    scanf("%d", &b->ISBN);

    //��������
    printf("please input Author:");
    scanf("%s", author);

    //�������
    printf("please input Classification:");
    scanf("%s", cf);
    
    //����������ֳ�����ռ�֮�󸳸�b
    b->classification = (char*)malloc(sizeof(char) * strlen(cf));
    b->Author = (char*)malloc(sizeof(char) * strlen(author));
    b->Title = (char*)malloc(sizeof(char) * strlen(name));
    strcpy(b->Title, name);
    strcpy(b->Author, author);
    strcpy(b->classification, cf);
    return SUCCESS;
}