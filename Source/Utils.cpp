/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-22 12:54:10
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 22:42:43
 */
#include"Utils.h"

/**
 * @brief ��ͣ
 */
void Pause(){
   system("pause");
}

/**
 * @brief �����Ļ
 */
void Clean(){
   system("cls");
}

/**
 * @brief ����ռ�
 */
char* CopyString(char str[]){
   int len = strlen(str);

   char* target = (char*)malloc(sizeof(char)*len);
   strcpy(target, str);
   return target;
}