/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-21 14:44:58
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-22 20:20:42
 */
#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

#include"Common.h"
#include"Book.h"
#define MAX_CHILD_NUMBER 3000

typedef struct BPlusTreeNode {
    int isRoot, isLeaf;
    int key_num;
    int key[MAX_CHILD_NUMBER];
    int pos[MAX_CHILD_NUMBER];
    BPlusTreeNode* child[MAX_CHILD_NUMBER];
    struct BPlusTreeNode* father;
    struct BPlusTreeNode* next;
    struct BPlusTreeNode* last;
    Book book[MAX_CHILD_NUMBER];
}BPlusTreeNode;

void Insert(BPlusTreeNode* Cur, int key, int pos, void* value);

void Delete(BPlusTreeNode* Cur, int key);

int BPlusTree_Find(int key);

void BPlusTree_SetMaxChildNumber(int number);

void BPlusTree_Init();

void BPlusTree_Destroy();

void Read_Data_And_Insert();

int BPlusTree_Insert(int key, int pos, BPlusTreeNode* value);

int BPlusTree_GetTotalNodes();

void BPlusTree_Query_Key(int key);

int Binary_Search(BPlusTreeNode* Cur, int key);

void BPlusTree_Query_Range(int l, int r);
  
void BPlusTree_Modify(int key, BPlusTreeNode* value);

void BPlusTree_Delete(int key);

void BPlusTree_Print();

#endif //BPLUSTREE_BPLUSTREE_H