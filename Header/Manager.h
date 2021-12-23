/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-23 17:37:21
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 22:46:43
 */
#ifndef MANAGER_H_INCLUDE
#define MANAGER_H_INCLUDE
#include"Common.h"

//管理员结构体
typedef struct manager{
    char name[10]; //管理员姓名
    char account[10]; //账号
    char password[10];//密码
    int power;
}manager, *Manager;

/**
 * @brief 初始化Manager
 * 
 * @param man 
 * @return Status 
 */
Status Man_Init(Manager &M);

#endif  //MANAGER_H_INCLUDE
