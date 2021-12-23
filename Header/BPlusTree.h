/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-21 14:44:58
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 01:03:21
 */
#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

#include"Common.h"
#include"Book.h"
#define MAX_CHILD_NUMBER 3000

typedef struct BPTNode {
    int isRoot, isLeaf;
    int key_num;
    int key[MAX_CHILD_NUMBER];
    int pos[MAX_CHILD_NUMBER];
    BPTNode* child[MAX_CHILD_NUMBER];
    struct BPTNode* father;
    struct BPTNode* next;
    struct BPTNode* last;
    Book book;
}BPTNode;

void Insert(BPTNode* Cur, int key, int pos, BPTNode* value);

void Delete(BPTNode* Cur, int key);

int BPlusTree_Find(int key);

extern void BPlusTree_SetMaxChildNumber(int number);

extern void BPlusTree_Init();

extern void BPlusTree_Destroy();

void Read_Data_And_Insert();

int BPlusTree_Insert(int key, int pos, BPTNode* value);

extern int BPlusTree_GetTotalNodes();

extern void BPlusTree_Query_Key(int key);

int Binary_Search(BPTNode* Cur, int key);

extern void BPlusTree_Query_Range(int l, int r);
  
extern void BPlusTree_Modify(int key, BPTNode* value);

extern void BPlusTree_Delete(int key);

void BPlusTree_Print();

#endif //BPLUSTREE_BPLUSTREE_H