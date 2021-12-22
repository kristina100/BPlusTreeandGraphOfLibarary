/*
 * @Descripttion: 
 * @Author: 
 * @Date: 2021-12-22 20:20:34
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-22 21:16:40
 */
#include"BPTree.h"r

int MaxChildNumber = 50;
int TotalNodes;
int QueryAnsNum;

//�����������root��������˽��sqt
Root Global_Root;

/**
 * @brief ��ʼ��B+�����
 */
BPTree BPT_CreateNode(){

    BPTree node = NULL;
    node = (BPTree)malloc(sizeof(BPNode));
    if(node == NULL)    
        return NULL;

    node->isLeaf = false;
    node->isRoot = false;
    node->keyNum = 0;
    node->nextLeaf = NULL;
    node->parent = NULL;
    node->preLeaf = NULL;
    node->record = NULL;
    TotalNodes++;

    return node;
}

/**
 * @brief ����,�ҵ� Cur->key[l]<=key �����ĺ���l
 */
int BPT_Search(BPTree Cur, int key){

    int l = 0;
    int r = Cur->keyNum;

    //keyС��key[0]
    if (key < Cur->key[l]) 
        return l;

    //key���ڵ���key[keyNum - 1]
    if (key >= Cur->key[r - 1] ) 
        return r - 1;

    while (l < r - 1){
        //�м�ֵmid
        int mid = (l + r) >> 1;
        if (Cur->key[mid] > key)    
            r = mid;
        else 
            l = mid;
    }
    return l;   
}

/**
 * @brief Cur(MaxChildNumber)���ֳ������֡�
 *        (1) Cur(0 ... Mid - 1)������ԭʼ��
 *        (2) Temp(Mid ... MaxChildNumber) with key[Mid]
 *        ���� Mid = MaxChildNumber / 2
 *        ע�⣬ֻ�е�Split()������ʱ���Żᴴ��һ���µĽڵ�
 * 
 * @param Cur 
 */
void BPT_Split(BPTree Cur){
    // ���� Cur(Mid .. MaxChildNumber) �� Temp(0 .. Temp->key_num)
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
    //����Cur��keyNum
    Cur->keyNum = Mid;

    //CurΪ�����
    if(Cur->isRoot){
        //�����µ��ڲ��ڵ�root,��������
        BPTree NewRoot = BPT_CreateNode();
        NewRoot->keyNum = 2;
        NewRoot->isLeaf = false;

        NewRoot->key[1] = Cur->key[0];
        NewRoot->ptr[1] = Cur;
        NewRoot->key[2] = Temp->key[0];
        NewRoot->ptr[2] = Temp;
        Cur->parent = Temp->parent = NewRoot;
        //��Ϊ�Ǹ����
        Cur->isRoot = false;
        if(Cur->isLeaf){
            Cur->nextLeaf = Temp;
            Temp->preLeaf = Cur;
        }
    }
    //CurΪҶ�ӽ���Ȳ����
    else{
        Temp->parent = Cur->parent;
        //����
        
    }
}