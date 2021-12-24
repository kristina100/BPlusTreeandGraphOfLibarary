/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-21 14:44:58
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-24 02:28:53
 */
#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

#include"Common.h"
#include"Book.h"
#define MAX_CHILD_NUMBER 3000

typedef struct BPTNode {
    Status isRoot, isLeaf;
    int key_num;
    KeyType key[MAX_CHILD_NUMBER + 1];
    int pos[MAX_CHILD_NUMBER + 1];
    struct BPTNode* ptr[MAX_CHILD_NUMBER + 1];
    struct BPTNode* parent;
    struct BPTNode* next;
    Book book;
}BPTNode, *BPTree;

typedef struct{
    BPTree target;  //找到的结点
    int pos;    //在找到结点中的关键字的位置
    Status tag;     //SUCCESS查找成功, FAIL查找失败 , ERROR错误
}Result;

void Insert(BPTree Cur, int key, int pos, BPTree value);

void Delete(BPTree Cur, int key);

int BPlusTree_Find(int key);

extern void BPlusTree_SetMaxChildNumber(int number);

extern void BPlusTree_Init();

extern void BPlusTree_Destroy();

void Read_Data_And_Insert();

int BPlusTree_Insert(int key, int pos, BPTree value);

extern int BPlusTree_GetTotalNodes();

extern void BPlusTree_Query_Key(int key);

int FindKeyPosition(BPTree Cur, int key);

extern void BPlusTree_Query_Range(int l, int r);
  
extern void BPlusTree_Modify(int key, BPTree value);

extern void BPlusTree_Delete(int key);

void BPlusTree_Print();

#endif //BPLUSTREE_BPLUSTREE_H