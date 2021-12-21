/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-21 14:44:58
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-21 20:59:14
 */
#ifndef BPLUSTREE_FILEDO_H
#define BPLUSTREE_FILEDO_H

#include"Common.h"

#define true 1
#define false 0
#define MAX_KEY 1000000000

/**
* Read_Buffer(char *input_file) -> buffer
*/
void Read_Buffer(char *input_file);

/** Read and insert records into B+tree */
void Read_Data_And_Insert();

int File_Modify(int pos, int key, char *value);

/** Delete (key, value) on data file */
void File_Delete(int pos);


/** Insert (key, value) on data file */
int File_Insert(int new_key, char* new_st);

void delete_test();
void modify_test();
void query_range_test();
void query_key_test();
void build_test();

#endif //BPLUSTREE_FILEDO_H