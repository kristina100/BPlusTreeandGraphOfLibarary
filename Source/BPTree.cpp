/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-22 20:20:34
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-22 20:44:00
 */
#include"BPTree.h"r

int MaxChildNumber = 50;
int TotalNodes;
int QueryAnsNum;

/**
 * @brief 初始化B+树结点
 */
BPTree BPT_CreateNode(){

    BPTree node = NULL;
    node = (BPTree)malloc(sizeof(BPNode));
    if(node == NULL)    
        return NULL;

    node->isLeaf = false;
    node->keyNum = 0;
    node->nextLeaf = NULL;
    node->parent = NULL;
    node->preLeaf = NULL;
    return node;
}

/**
 * @brief 搜索,找到 Cur->key[l]<=key 的最大的孩子l
 */
int BPT_Search(BPTree Cur, int key){

    int l = 0;
    int r = Cur->keyNum;

    //key小于key[0]
    if (key < Cur->key[l]) 
        return l;

    //key大于等于key[keyNum - 1]
    if (key >= Cur->key[r - 1] ) 
        return r - 1;

    while (l < r - 1){
        //中间值mid
        int mid = (l + r) >> 1;
        if (Cur->key[mid] > key)    
            r = mid;
        else 
            l = mid;
    }
    return l;   
}

/**
 * @brief Cur(MaxChildNumber)被分成两部分。
 *        (1) Cur(0 ... Mid - 1)，带有原始键
 *        (2) Temp(Mid ... MaxChildNumber) with key[Mid]
 *        其中 Mid = MaxChildNumber / 2
 *        注意，只有当Split()被调用时，才会创建一个新的节点
 * 
 * @param Cur 
 */
void BPT_Split(BPTree Cur){
    // 复制 Cur(Mid .. MaxChildNumber) 到 Temp(0 .. Temp->key_num)
    BPTree Temp = BPT_CreateNode();
    BPTree ch = NULL;
    int Mid = MaxChildNumber >> 1;

    // Temp's depth == Cur's depth
    Temp->isLeaf = Cur->isLeaf; 
    Temp->key_num = MaxChildNumber - Mid;

    for (int i = Mid; i < MaxChildNumber; i++) {
    
        Temp->key[i - Mid] = Cur->key[i];
        if (Temp->isLeaf) {
            Temp->pos[i - Mid] = Cur->pos[i];
        } else {
            ch = Temp->child[i - Mid];
            ch->father = Temp;
        }
    }


}