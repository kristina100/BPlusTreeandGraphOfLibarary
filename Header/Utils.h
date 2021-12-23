/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-22 12:54:00
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 22:43:42
 */
#ifndef UTILS_H_INCLUDE
#define UTILS_H_INCLUDE
#include"Common.h"
#include"Book.h"

/**
 * @brief 暂停
 */
void Pause();

/**
 * @brief 清空屏幕
 */
void Clean();

/**
 * @brief 根据长度分配空间并复制字符串
 * 
 * @param target 
 * @param len 
 */
char* CopyString(char* str);

#endif  