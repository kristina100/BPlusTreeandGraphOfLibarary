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

//����Ա�ṹ��
typedef struct manager{
    char name[10]; //����Ա����
    char account[10]; //�˺�
    char password[10];//����
    int power;
}manager, *Manager;

/**
 * @brief ��ʼ��Manager
 * 
 * @param man 
 * @return Status 
 */
Status Man_Init(Manager &M);

#endif  //MANAGER_H_INCLUDE
