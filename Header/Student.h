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

//我的书
typedef struct myBook{
    Book book;//借的书
    Book next;//下一本书
}myBook,*MyBook;

//学生结构体
typedef struct student{
    char name[10]; //学生姓名
    char account[10];  //账号
    char ID[10];   //学号
    char password[10];//密码
    MyBook book;    //我借的书
    int power;
}student, *Stu;

/**
 * @brief 初始化Stu
 * 
 * @param stu 
 * @return Status 
 */
Status Stu_Init(Stu &stu);

/**
 * @brief 学生操作
 * 
 */
void Stu_Operation(Stu &stu);

/**
 * @brief 打印学生选项
 * 
 */
void Stu_Options();

/**
 * @brief 学生借书
 * 
 */
Status Stu_Borrow();

/**
 * @brief 学生还书
 * 
 */
Status Stu_return();

/**
 * @brief 查看我的信息
 * 
 */
void Stu_MyInfo();

/**
 * @brief 找回密码
 * 
 */
Status Stu_FindPassword();

/**
 * @brief 更改密码
 * 
 * @return Status 
 */
Status Stu_ChangePassword();

#endif  //STUDENT_H_INCLUDE