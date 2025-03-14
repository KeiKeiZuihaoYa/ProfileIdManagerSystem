#include "bstree.h"
#include <string>
#include <vector>
#include <iostream>

void Insert_node(BTNode **root, DataType data)
{
    if (*root == NULL)
    {
        *root = (BTNode *)malloc(sizeof(BTNode));
        if (!*root)
        {
            std::cout << "Memory ERROR! " << '\n';
            exit(-1);
        }
        (*root)->data = data;
    }
    else if ((*root)->data <= data)
        Insert_node(&(*root)->right, data);
    else if ((*root)->data > data)
        Insert_node(&(*root)->left, data);
}

BTNode *Create_sortBtree(const std::vector<DataType> &arr, const int &size)
{
    if (arr.empty())
        return NULL;
    else
    {
        BTNode *T = NULL;
        for (int i = 0; i < size; i++)
        {
            Insert_node(&T, arr[i]);
        }
        return T;
    }
}

BTNode *Btree_search(BTNode *root, DataType target)
{
    if (!root)
        return NULL;
    if (target == root->data)
    {
        return root;
    }
    return target > root->data ? Btree_search(root->right, target) : Btree_search(root->left, target);
}

void Btree_del(BTNode *T, DataType l)
{
    if (!T)
    {
        std::cout << "Emept! " << '\n';
        return;
    }
    // 找到这个要删除节点的父节点
    BTNode *p = T, *f = NULL;
    while (p)
    {
        if (p->data == l)
        {
            break;
        }
        f = p;
        p = l > p->data ? p->right : p->left;
    }
    if (!p)
    {
        std::cout << "This node is not existing! " << '\n';
        return;
    }
    BTNode *target = p; // 此时的要删除目标节点
    BTNode *par = f;    // 此时要删除节点的父节点

    if (!target->left && !target->right)
    {
        (target->data > par->data ? par->right : par->left) = NULL;
        free(target);
    }
    else if (!target->left || !target->right)
    {
        BTNode *tmp = target->left ? target->left : target->right;
        (target->data > par->data ? par->right : par->left) = tmp;
        free(target);
    }
    else
    {
        BTNode *Lchild = target->left;
        BTNode *Lchild_par = NULL; // 要找的替换节点的父节点
        while (Lchild->right != NULL)
        {
            Lchild_par = Lchild;
            Lchild = Lchild->right;
        }

        Lchild_par->right = Lchild->left;
        target->data = Lchild->data;
        free(Lchild);
    }
    std::cout << "Deleting successfully! " << '\n';
}

void Destory_btree(BTNode *T)
{
    if (!T)
        return;
    BTNode *cur = T;
    if (cur->left)
        Destory_btree(cur->left);
    if (cur->right)
        Destory_btree(cur->right);
    free(T);
}