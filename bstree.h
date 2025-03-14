// 防止头文件被重复包含
#ifndef BSTREE_H
#define BSTREE_H
#include <string>
#include <vector>

// 定义二叉排序树节点结构体
typedef struct node
{
    std::string sfz, name, phone;
    int age;
    bool operator<(const node &a) const
    {
        return sfz < a.sfz;
    }
    bool operator>(const node &a) const
    {
        return sfz > a.sfz;
    }
    bool operator==(const node &a) const
    {
        return sfz == a.sfz;
    }
    bool operator<=(const node &a) const
    {
        return sfz <= a.sfz;
    }
};

typedef node DataType;
typedef struct BTNode
{
    DataType data;
    struct BTNode *left = nullptr;
    struct BTNode *right = nullptr;
} BTNode;

// 函数声明
void Insert_node(BTNode **T, DataType data);
BTNode *Create_sortBtree(const std::vector<DataType> &arr, int size);
BTNode *Btree_search(BTNode *root, DataType target);
void Btree_del(BTNode *T, DataType data);
void Destory_btree(BTNode *T);

#endif