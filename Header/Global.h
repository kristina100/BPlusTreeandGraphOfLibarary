/*
 * @Descripttion: 全局变量 .h文件
 * @Author: Hx
 * @Date: 2021-12-21 20:46:24
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-22 12:51:19
 */
#ifndef GLOBAL_VARIABLE
#define GLOBAL_VARIABLE

// file
extern char input_file[100];
extern char output_file[100];
extern char *buffer;
extern int fsize;

// record
extern int new_key;
extern int new_pos;
extern int new_len;
extern char new_st[12];

// data
const int TotalRecords = 10000000;
extern int validRecords;

// test
extern int keys[10000000];
extern int key_num;


#endif //GLOBAL_VARIABLE