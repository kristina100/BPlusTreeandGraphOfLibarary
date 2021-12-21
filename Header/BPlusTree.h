/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-21 14:44:58
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-21 22:09:40
 */
#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

#include"Common.h"
#include"Book.h"
#define MAX_CHILD_NUMBER 3200

typedef struct BPlusTreeNode {
    int isRoot, isLeaf;
    int key_num;
    int key[MAX_CHILD_NUMBER];
    int pos[MAX_CHILD_NUMBER];
    void* child[MAX_CHILD_NUMBER];
    struct BPlusTreeNode* father;
    struct BPlusTreeNode* next;
    struct BPlusTreeNode* last;
    Book books[MAX_CHILD_NUMBER];
}BPlusTreeNode;

void Insert(BPlusTreeNode* Cur, int key, int pos, void* value);

void Delete(BPlusTreeNode* Cur, int key);

int BPlusTree_Find(int key);

extern void BPlusTree_SetMaxChildNumber(int number);

extern void BPlusTree_Init();

extern void BPlusTree_Destroy();

void Read_Data_And_Insert();

extern int BPlusTree_Insert(int key, int pos, void* value);

extern int BPlusTree_GetTotalNodes();

extern void BPlusTree_Query_Key(int key);

int Binary_Search(BPlusTreeNode* Cur, int key);

extern void BPlusTree_Query_Range(int l, int r);

extern void BPlusTree_Modify(int key, void* value);

extern void BPlusTree_Delete(int key);

#endif //BPLUSTREE_BPLUSTREE_H