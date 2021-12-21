//
// Created by HUAWEI on 2021-12-21.
//

#ifndef BPLUSTREE_FILEDO_H
#define BPLUSTREE_FILEDO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0
#define MAX_KEY 1000000000

// file
char input_file[100];
char output_file[100];
char *buffer;
int fsize;
// record
int new_key, new_pos, new_len;
char new_st[12];
// data
const int TotalRecords = 10000000;
int validRecords;
// test
int keys[10000000], key_num;

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
