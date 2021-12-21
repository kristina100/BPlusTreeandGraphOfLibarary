//
// Created by HUAWEI on 2021-12-21.
//

#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

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
} BPlusTreeNode;

void Insert(BPlusTreeNode* Cur, int key, int pos, void* value);
void Delete(BPlusTreeNode* Cur, int key);

int BPlusTree_Find(int key);

extern void BPlusTree_SetMaxChildNumber(int);
extern void BPlusTree_Init();
extern void BPlusTree_Destroy();
void Read_Data_And_Insert();
extern int BPlusTree_Insert(int, int, void*);
extern int BPlusTree_GetTotalNodes();
extern void BPlusTree_Query_Key(int);
int Binary_Search(BPlusTreeNode* Cur, int key);
extern void BPlusTree_Query_Range(int, int);
extern void BPlusTree_Modify(int, void*);
extern void BPlusTree_Delete(int);

#endif //BPLUSTREE_BPLUSTREE_H
