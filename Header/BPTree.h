/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-22 20:15:40
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-22 20:49:16
 */
#ifndef _BPTREE_H_INCLUDE_
#define _BPTREE_H_INCLUDE_

#include"Common.h"
#include"Book.h"
#define MAX_CHILD_NUMBER 3000

//B+树结构体
typedef struct BPTNode{
    Status isLeaf;              //标记是否为叶子结点,叶子为TRUE
    int keyNum;                 //结点中关键字的数量
    struct BPTNode *parent;     //指向双亲结点
    struct BPTNode *nextLeaf;   //下一个叶子结点
    struct BPTNode *preLeaf;    //上一个叶子结点
    struct BPTNode *ptr[M + 1]; //结点中指向子树的指针数组,0号单元不使用
    KeyType key[MAX_CHILD_NUMBER + 1];//结点中的关键字数组,0号单元不使用
    Rcd record; //数据域
}BPNode, *BPTree;

typedef struct {
    BPTree root;    //树根
    BPTree sqt;     //树底左端
}Root;

//RcdType结构
typedef struct RcdType{
    Book book[M + 1];   //记录的书,0号单元不使用
}RcdType, *Rcd;

//查找结果结构体
typedef struct{
    BPTree target;  //找到的结点
    KeyType key;    //在找到结点中的关键字
    Status tag;     //SUCCESS查找成功, FAIL查找失败 , ERROR错误
}Result;

/**
 * @brief 初始化B+树结点
 * 
 * @return BPTree 
 */
BPTree BPT_CreateNode();

/**
 * @brief 搜索,找到 Cur->key[i]<=key 的最大的孩子i
 * 
 * @param p 
 * @param key 
 * @return int 
 */
int BPT_Search(BPTree Cur, int key);

/**
 * @brief Cur(MaxChildNumber)被分成两部分。
 *        (1) Cur(0 ... Mid - 1)，带有原始键
 *        (2) Temp(Mid ... MaxChildNumber) with key[Mid]
 *        其中 Mid = MaxChildNumber / 2
 *        注意，只有当Split()被调用时，才会创建一个新的节点
 * 
 * @param Cur 
 */
void BPT_Split(BPTree Cur);

#endif  //_BPTREE_H_INCLUDE_