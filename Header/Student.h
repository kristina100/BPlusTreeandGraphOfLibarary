/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-23 14:33:25
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 22:47:03
 */
#ifndef STUDENT_H_INCLUDE
#define STUDENT_H_INCLUDE
#include"Common.h"
#include"Book.h"

//�ҵ���
typedef struct myBook{
    Book book;//�����
    Book next;//��һ����
}myBook,*MyBook;

//ѧ���ṹ��
typedef struct student{
    char name[10]; //ѧ������
    char account[10];  //�˺�
    char ID[10];   //ѧ��
    char password[10];//����
    MyBook book;    //�ҽ����
    int power;
}student, *Stu;

/**
 * @brief ��ʼ��Stu
 * 
 * @param stu 
 * @return Status 
 */
Status Stu_Init(Stu &stu);

/**
 * @brief ѧ������
 * 
 */
void Stu_Operation(Stu &stu);

/**
 * @brief ��ӡѧ��ѡ��
 * 
 */
void Stu_Options();

/**
 * @brief ѧ������
 * 
 */
Status Stu_Borrow();

/**
 * @brief ѧ������
 * 
 */
Status Stu_return();

/**
 * @brief �鿴�ҵ���Ϣ
 * 
 */
void Stu_MyInfo();

/**
 * @brief �һ�����
 * 
 */
Status Stu_FindPassword();

/**
 * @brief ��������
 * 
 * @return Status 
 */
Status Stu_ChangePassword();

#endif  //STUDENT_H_INCLUDE