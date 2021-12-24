#include"FileDo.h"
#include"BPlusTree.h"
#include"Global.h"

struct BPTree Root;
int MaxChildNumber = 50;
int TotalNodes;
int QueryAnsNum;

/** 建立新的结点 */
BPTree New_BPlusTreeNode() {
    struct BPTree p = (struct BPTree)malloc(sizeof(struct BPTNode));
    p->isRoot = false;
    p->isLeaf = false;
    p->key_num = 0;
    p->ptr[0] = NULL;
    p->parent = NULL;
    p->next = NULL;
    p->last = NULL;
    p->book = NULL;
    TotalNodes++;
    return p;
}

/** 
 * 根据key的大小在结点的Key[1...keynum]中找到位置i,
 * 使T->key[i] <= key < T->key[i + 1]
 * */
int FindKeyPosition(BPTree Cur, int key)
{
    int l = 1, r = Cur->key_num;
    if (key < Cur->key[l]) 
        return l;

    if (key >= Cur->key[r]) 
        return r;

    int mid;
    while (l < r - 1) {
        mid = (l + r) >> 1;
        if (Cur->key[mid] > key)
            r = mid;
        else
            l = mid;
    }
    return l;
}

/**
 * Cur(MaxChildNumber)被分成两部分。
 * (1) Cur(0 ... Mid - 1)，带有原始键
 * (2) Temp(Mid ... MaxChildNumber) with key[Mid]
 * 其中 Mid = MaxChildNumber / 2
 * 注意，只有当Split()被调用时，才会创建一个新的节点
 */
void Split(BPTree Cur) {
    // copy Cur(Mid .. MaxChildNumber) -> Temp(0 .. Temp->key_num)
    BPTree Temp = New_BPlusTreeNode();
    BPTree ch;
    int Mid = MaxChildNumber >> 1;
    Temp->isLeaf = Cur->isLeaf; // Temp's depth == Cur's depth
    Temp->key_num = MaxChildNumber - Mid;
 
    for (int i = Mid; i < MaxChildNumber; i++) {
        Temp->ptr[i - Mid] = Cur->ptr[i];
        Temp->key[i - Mid] = Cur->key[i];
        if (Temp->isLeaf) {
            Temp->pos[i - Mid] = Cur->pos[i];
        } else {
            ch = Temp->ptr[i - Mid];
            ch->parent = Temp;
        }
    }

    // Change Cur
    Cur->key_num = Mid;
    // Insert Temp
    if (Cur->isRoot) {
        // Create a new Root, the depth of Tree is increased
        Root = New_BPlusTreeNode();
        Root->key_num = 2;
        Root->isRoot = true;
        Root->key[0] = Cur->key[0];
        Root->ptr[0] = Cur;
        Root->key[1] = Temp->key[0];
        Root->ptr[1] = Temp;
        Cur->parent = Temp->parent = Root;
        Cur->isRoot = false;
        if (Cur->isLeaf) {
            Cur->next = Temp;
            Temp->last = Cur;
        }
    } else {
        // Try to insert Temp to Cur->parent
        Temp->parent = Cur->parent;
        Insert(Cur->parent, Cur->key[Mid], -1, Temp);
    } 
}

/** Insert (key, value) into Cur, if Cur is full, then split it to fit the definition of B+tree */
void Insert(BPTree Cur, int key, int pos, BPTree value){
    int i, ins;
    if (key < Cur->key[0]) 
        ins = 0; 

    else ins = FindKeyPosition(Cur, key) + 1;

    //调整key和pos位置
    for (i = Cur->key_num; i > ins; i--) {
        Cur->key[i] = Cur->key[i - 1];
        Cur->ptr[i] = Cur->ptr[i - 1];
        if (Cur->isLeaf) 
            Cur->pos[i] = Cur->pos[i - 1];
    }

    //插入新key
    Cur->key_num++;
    Cur->key[ins] = key;
    Cur->ptr[ins] = value;
    Cur->pos[ins] = pos;

    // make links on leaves连接叶子
    if (Cur->isLeaf == false) { 
        BPTree firstChild = Cur->ptr[0];
        if (firstChild->isLeaf == true) { // which means value is also a leaf as ptr[0]
            BPTree temp = value;
            if (ins > 0) {
                BPTree prevChild;
                BPTree succChild;
                prevChild = Cur->ptr[ins - 1];
                succChild = prevChild->next;
                prevChild->next = temp;
                temp->next = succChild;
                temp->last = prevChild;
                if (succChild != NULL) succChild->last = temp;
            } else {
                // do not have a prevChild, then refer next directly
                // updated: the very first record on B+tree, and will not come to this case
                temp->next = Cur->ptr[1];
                printf("this happens\n");
            }
        }
    }
    if (Cur->key_num == MaxChildNumber) // children is full
        Split(Cur);
}

/** Resort(Give, Get) make their no. of children average */
void Resort(BPTree Left, BPTree Right) {
    int total = Left->key_num + Right->key_num;
    BPTree temp;
    if (Left->key_num < Right->key_num) {
        int leftSize = total >> 1;
        int i = 0, j = 0;
        while (Left->key_num < leftSize) {
            Left->key[Left->key_num] = Right->key[i];
            Left->ptr[Left->key_num] = Right->ptr[i];
            if (Left->isLeaf) {
                Left->pos[Left->key_num] = Right->pos[i];
            } else {
                temp = Right->ptr[i];
                temp->parent = Left;
            }
            Left->key_num++;
            i++;
        }
        while (i < Right->key_num) {
            Right->key[j] = Right->key[i];
            Right->ptr[j] = Right->ptr[i];
            if (Right->isLeaf) Right->pos[j] = Right->pos[i];
            i++;
            j++;
        }
        Right->key_num = j;
    } else {
        int leftSize = total >> 1;
        int i, move = Left->key_num - leftSize, j = 0;
        for (i = Right->key_num - 1; i >= 0; i--) {
            Right->key[i + move] = Right->key[i];
            Right->ptr[i + move] = Right->ptr[i];
            if (Right->isLeaf) Right->pos[i + move] = Right->pos[i];
        }
        for (i = leftSize; i < Left->key_num; i++) {
            Right->key[j] = Left->key[i];
            Right->ptr[j] = Left->ptr[i];
            if (Right->isLeaf) {
                Right->pos[j] = Left->pos[i];
            } else {
                temp = Left->ptr[i];
                temp->parent = Right;
            }
            j++;
        }
        Left->key_num = leftSize;
        Right->key_num = total - leftSize;
    }
}

/**
重新分配Cur，使用以下策略。
 * (1) 与右边的兄弟一起resort
 * (2) 与左边的兄弟resort
 * (3) 与右边的兄弟合并
 * (4) 与左翼兄弟合并
 * 在这种情况下，根只有一个孩子，把这个孩子设为根。
 */
void Redistribute(BPTree Cur) {
    if (Cur->isRoot) {
        if (Cur->key_num == 1 && !Cur->isLeaf) {
            Root = Cur->ptr[0];
            Root->isRoot = true;
            free(Cur);
        }
        return;
    }
    BPTree Father = Cur->parent;
    BPTree prevChild;
    BPTree succChild;
    BPTree temp;
    int my_index = FindKeyPosition(Father, Cur->key[0]);

    if (my_index + 1 < Father->key_num) {
        succChild = Father->ptr[my_index + 1];
        if ((succChild->key_num - 1) * 2 >= MaxChildNumber) { // at least can move one ptr to Cur
            Resort(Cur, succChild); // (1) resort with right ptr
            Father->key[my_index + 1] = succChild->key[0];
            return;
        }
    }
    if (my_index - 1 >= 0) {
        prevChild = Father->ptr[my_index - 1];
        if ((prevChild->key_num - 1) * 2 >= MaxChildNumber) {
            Resort(prevChild, Cur); // (2) resort with left ptr
            Father->key[my_index] = Cur->key[0];
            return;
        }
    }
    if (my_index + 1 < Father->key_num) { // (3) merge with right ptr
        int i = 0;
        while (i < succChild->key_num) {
            Cur->key[Cur->key_num] = succChild->key[i];
            Cur->ptr[Cur->key_num] = succChild->ptr[i];
            if (Cur->isLeaf) {
                Cur->pos[Cur->key_num] = succChild->pos[i];
            } else {
                temp = succChild->ptr[i];
                temp->parent = Cur;
            }
            Cur->key_num++;
            i++;
        }
        Delete(Father, succChild->key[0]); // delete right ptr
        return;
    }
    if (my_index - 1 >= 0) { // (4) merge with left ptr
        int i = 0;
        while (i < Cur->key_num) {
            prevChild->key[prevChild->key_num] = Cur->key[i];
            prevChild->ptr[prevChild->key_num] = Cur->ptr[i];
            if (Cur->isLeaf) {
                prevChild->pos[prevChild->key_num] = Cur->pos[i];
            } else {
                temp = (BPTree)(Cur->ptr[i]);
                temp->parent = prevChild;
            }
            prevChild->key_num++;
            i++;
        }
        Delete(Father, Cur->key[0]); // delete left ptr
        return;
    }
    printf("What?! you're the only ptr???\n"); // this won't happen
}

/** 从Cur中删除键，如果孩子的数量<(MaxChildNUmber / 2)，则与兄弟合并。 */
void Delete(BPTree Cur, int key) {
    int i, del = FindKeyPosition(Cur, key);
    BPTree delChild = Cur->ptr[del];
    for (i = del; i < Cur->key_num - 1; i++) {
        Cur->key[i] = Cur->key[i + 1];
        Cur->ptr[i] = Cur->ptr[i + 1];
        if (Cur->isLeaf) Cur->pos[i] = Cur->pos[i + 1];
    }
    Cur->key_num--;
    if (Cur->isLeaf == false) { // make links on leaves
        BPTree firstChild = Cur->ptr[0];
        if (firstChild->isLeaf == true) { // which means delChild is also a leaf
            BPTree temp = delChild;
            BPTree prevChild = temp->last;
            BPTree succChild = temp->next;
            if (prevChild != NULL) prevChild->next = succChild;
            if (succChild != NULL) succChild->last = prevChild;
        }
    }
    if (del == 0 && !Cur->isRoot) { // some fathers' key should be changed
        BPTree temp = Cur;
        while (!temp->isRoot && temp == temp->parent->ptr[0]) {
            temp->parent->key[0] = Cur->key[0];
            temp = temp->parent;
        }
        if (!temp->isRoot) {
            temp = temp->parent;
            int i = FindKeyPosition(temp, key);
            temp->key[i] = Cur->key[0];
        }
    }
    free(delChild);
    if (Cur->key_num * 2 < MaxChildNumber)
        Redistribute(Cur);
}

/** 找到一个键位于其中的叶子节点
 * 修改表示键是否应该影响树
 */
Result Find(int key) {
    BPTree Cur = Root;
    while (1) {
        if (Cur->isLeaf == true)
            break;
        if (key < Cur->key[1]) {
            Cur = Cur->ptr[1];
        } else {
            int i = FindKeyPosition(Cur, key);
            Cur = Cur->ptr[i];
        }
    }

    Result res;
    res.pos = FindKeyPosition(Cur,key);
    res.target = Cur;
    if(key == Cur->key[pos])
        res.tag = SUCCESS;
    else res.tag = FALSE;
    
    return res;
}

/** 递归销毁 */
void Destroy(BPTree Cur) {
    if (Cur->isLeaf == true) {
        int i;
        for (i = 0; i < Cur->key_num; i++)
            free(Cur->ptr[i]);
    } else {
        int i;
        for (i = 0; i < Cur->key_num; i++)
            Destroy(Cur->ptr[i]);
    }
    free(Cur);
}

/** 打印子树 */
void Print(BPTree Cur) {
    int i;
    for (i = 0; i < Cur->key_num; i++)
        printf("%d ", Cur->key[i]);
    printf("\n");
    if (!Cur->isLeaf) {
        for (i = 0; i < Cur->key_num; i++)
            Print(Cur->ptr[i]);
    }
}

/** 插入新树 */
int BPlusTree_Insert(int key, int pos, BPTree value) {
    BPTree Leaf = Find(key, true);
    int i = FindKeyPosition(Leaf, key);

    //key已存在
    if (Leaf->key[i] == key) return false;

    Insert(Leaf, key, pos, value);
    return true;
}

/** Interface: 查询所有键值符合该键值的记录 = query_key  */
void BPlusTree_Query_Key(int key) {
    BPTree Leaf = Find(key, false);
    QueryAnsNum = 0;
    int i;
    for (i = 0; i < Leaf->key_num; i++) {
        //printf("%d ", Leaf->key[i]);
        if (Leaf->key[i] == key) {
            QueryAnsNum++;
            if (QueryAnsNum < 20) 
                printf("[no.%d	key = %d, value = %s]\n", QueryAnsNum, Leaf->key[i], Leaf->ptr[i]->book->Title);
        }
    }
    printf("Total number of answers is: %d\n", QueryAnsNum);
}

/** Interface: 查询所有键值满足query_l <= key <= query_r的记录。 */
void BPlusTree_Query_Range(int l, int r) {
    BPTree Leaf = Find(l, false);
    QueryAnsNum = 0;
    int i;
    for (i = 0; i < Leaf->key_num; i++) {
        //printf("%d ", Leaf->key[i]);
        if (Leaf->key[i] >= l) break;
    }
    int finish = false;
    while (!finish) {
        while (i < Leaf->key_num) {
            if (Leaf->key[i] > r) {
                finish = true;
                break;
            }
            QueryAnsNum++;
            if (QueryAnsNum == 20) printf("...\n");
            // if (QueryAnsNum < 20) printf("[no.%d	key = %d, value = %s]\n", QueryAnsNum, Leaf->key[i], Leaf->ptr[i]->book->Title);
            i++;
        }
        if (finish || Leaf->next == NULL) break;
        Leaf = Leaf->next;
        i = 0;
    }
    printf("Total number of answers is: %d\n", QueryAnsNum);
}

/** Interface: 查找给定键的位置 */
int BPlusTree_Find(int key) {
    BPTree Leaf = Find(key, false);
    int i = FindKeyPosition(Leaf, key);
    if (Leaf->key[i] != key) return -1; // don't have this key
    return Leaf->pos[i];
}

/** Interface: 修改给定键上的值 */
void BPlusTree_Modify(int key, BPTree value) {
    BPTree Leaf = Find(key, false);
    int i = FindKeyPosition(Leaf, key);
    if (Leaf->key[i] != key) return; // don't have this key
    // printf("Modify: key = %d, original value = %s, new value = %s\n", key, Leaf->ptr[i]->book->ISBN, value->book->Title);
    free(Leaf->ptr[i]);
    Leaf->ptr[i] = value;
}

/** Interface: 在给定的键上删除值 */
void BPlusTree_Delete(int key) {
    BPTree Leaf = Find(key, false);
    int i = FindKeyPosition(Leaf, key);
    if (Leaf->key[i] != key) return; // don't have this key
    // printf("Delete: key = %d, original value = %s\n", key, Leaf->ptr[i]->book->Title);
    Delete(Leaf, key);
}

/** Interface: 销毁b+树 */
void BPlusTree_Destroy() {
    if (Root == NULL) return;
    printf("Now destroying B+tree ..\n");
    Destroy(Root);
    Root = NULL;
    printf("Done.\n");
}

/** Interface:初始化 */
void BPlusTree_Init() {
    BPlusTree_Destroy();
    Root = New_BPlusTreeNode();
    Root->isRoot = true;
    Root->isLeaf = true;
    TotalNodes = 0;
}

/**
 * Interface: setting MaxChildNumber in your program
 * A suggest value is cube root of the no. of records
 */
void BPlusTree_SetMaxChildNumber(int number) {
    MaxChildNumber = number + 1;
}

/** Interface: print the tree (DEBUG use)*/
void BPlusTree_Print() {
    struct BPTree Leaf = Find(1000000000, false);
    int cnt = 0;
    while (Leaf != NULL) {
        int i;
        for (i = Leaf->key_num - 1; i >= 0; i--) {
            printf("%4d ", Leaf->key[i]);
            if (++cnt % 20 == 0) printf("\n");
        }
        Leaf = Leaf->last;
    }
}

/** Interface: Total Nodes */
int BPlusTree_GetTotalNodes() {
    return TotalNodes;
}