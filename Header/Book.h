/*
 * @Descripttion: Book�� .hͷ�ļ�
 * @Author: Hx
 * @Date: 2021-12-12 23:08:25
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-21 22:09:42
 */
#ifndef BOOK_H_INCLUDE
#define BOOK_H_INCLUDE

#include"Common.h"

typedef struct book{
    KeyType ISBN;   //��ı��
    char *name;     //����
    char *Author;   //����
    char *classification; //�������
    int count;  //��Ŀ����
    int Lent;   //�������
}book, *Book;

#endif //BOOK_H_INCLUDE