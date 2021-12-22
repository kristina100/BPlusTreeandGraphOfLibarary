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

//B+���ṹ��
typedef struct BPTNode{
    Status isLeaf;              //����Ƿ�ΪҶ�ӽ��,Ҷ��ΪTRUE
    int keyNum;                 //����йؼ��ֵ�����
    struct BPTNode *parent;     //ָ��˫�׽��
    struct BPTNode *nextLeaf;   //��һ��Ҷ�ӽ��
    struct BPTNode *preLeaf;    //��һ��Ҷ�ӽ��
    struct BPTNode *ptr[M + 1]; //�����ָ��������ָ������,0�ŵ�Ԫ��ʹ��
    KeyType key[MAX_CHILD_NUMBER + 1];//����еĹؼ�������,0�ŵ�Ԫ��ʹ��
    Rcd record; //������
}BPNode, *BPTree;

typedef struct {
    BPTree root;    //����
    BPTree sqt;     //�������
}Root;

//RcdType�ṹ
typedef struct RcdType{
    Book book[M + 1];   //��¼����,0�ŵ�Ԫ��ʹ��
}RcdType, *Rcd;

//���ҽ���ṹ��
typedef struct{
    BPTree target;  //�ҵ��Ľ��
    KeyType key;    //���ҵ�����еĹؼ���
    Status tag;     //SUCCESS���ҳɹ�, FAIL����ʧ�� , ERROR����
}Result;

/**
 * @brief ��ʼ��B+�����
 * 
 * @return BPTree 
 */
BPTree BPT_CreateNode();

/**
 * @brief ����,�ҵ� Cur->key[i]<=key �����ĺ���i
 * 
 * @param p 
 * @param key 
 * @return int 
 */
int BPT_Search(BPTree Cur, int key);

/**
 * @brief Cur(MaxChildNumber)���ֳ������֡�
 *        (1) Cur(0 ... Mid - 1)������ԭʼ��
 *        (2) Temp(Mid ... MaxChildNumber) with key[Mid]
 *        ���� Mid = MaxChildNumber / 2
 *        ע�⣬ֻ�е�Split()������ʱ���Żᴴ��һ���µĽڵ�
 * 
 * @param Cur 
 */
void BPT_Split(BPTree Cur);

#endif  //_BPTREE_H_INCLUDE_