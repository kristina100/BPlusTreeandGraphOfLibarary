/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-23 15:51:52
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 21:37:48
 */
#include"Common.h"
#include"Student.h"
#include"Manager.h"

/**
 * @brief ��ӡ��¼����
 * 
 */
void Print_Login_Options();

/**
 * @brief ��¼����
 */
void Login_Operation();

/**
 * @brief ѧ����¼
 * 
 * @return Stu 
 */
Stu Login_Stu();

/**
 * @brief ע�����,mode == 0 Ϊѧ��ע��, 1Ϊ����Աע��
 * 
 * @param mode 
 * @return Status 
 */
Status Register_Operation(int mode);

/**
 * @brief ����ѧ���͹���Ա
 * 
 */
Status Register_Spilt();

/**
 * @brief ��ӡע��ѡ��
 * 
 */
void Print_Register_Option();
