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
 * @brief 打印登录界面
 * 
 */
void Print_Login_Options();

/**
 * @brief 登录操作
 */
void Login_Operation();

/**
 * @brief 学生登录
 * 
 * @return Stu 
 */
Stu Login_Stu();

/**
 * @brief 注册操作,mode == 0 为学生注册, 1为管理员注册
 * 
 * @param mode 
 * @return Status 
 */
Status Register_Operation(int mode);

/**
 * @brief 分流学生和管理员
 * 
 */
Status Register_Spilt();

/**
 * @brief 打印注册选项
 * 
 */
void Print_Register_Option();
