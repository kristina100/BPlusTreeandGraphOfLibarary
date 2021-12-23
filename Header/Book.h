/*
 * @Descripttion: Book�� .hͷ�ļ�
 * @Author: Hx
 * @Date: 2021-12-12 23:08:25
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 15:11:27
 */
#ifndef BOOK_H_INCLUDE
#define BOOK_H_INCLUDE

#include"Common.h"

typedef struct book{
    int ISBN;   //��ı��
    char *Title; //����
    char *Author;   //����
    char *press;    //������
    char *publishing_year;  //����ʱ�� 
    char *classification; //�������
    float price;    //�۸�
    Status status;  //״̬
}book, *Book;

/**
 * @brief �����鱾��Ϣ
 * 
 * @return Book 
 */
Status inputBookInfo(Book &book);



#endif //BOOK_H_INCLUDE