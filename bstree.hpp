#ifndef BSTREE_HPP
#define BSTREE_HPP
// bstree.hpp

#include <string>
#include <vector>
#include <iostream>

class BSTree
{
public:
    struct DataType
    {
        std::string sfz;
        std::string name;
        std::string phone;
        int age;

        // 重载各种使用到的操作符
        bool operator<(const DataType &a) const { return sfz < a.sfz; }
        bool operator>(const DataType &a) const { return sfz > a.sfz; }
        bool operator==(const DataType &a) const { return sfz == a.sfz; }
        bool operator<=(const DataType &a) const { return sfz <= a.sfz; }
    };

    // 貌似是确保安全的
    BSTree() = default;
    ~BSTree() { clear(); }

    void createFromArray(const std::vector<DataType> &arr)
    {
        clear();
        for (const auto &item : arr)
            insertNode(&root, item);
    }

    const DataType *search(const DataType &target) const // 改为私域查询， 同时返回 const DataType* 确保不被修改
    {
        BTNode *found = findNode(root, target);
        return found ? &found->data : nullptr;
    }

    void remove(const DataType &data)
    {
        if (!root) // 还没有身份信息呢，删什么
        {
            std::cout << "Empty tree!" << std::endl;
            return;
        }

        BTNode *parent = nullptr;
        BTNode *current = root;

        while (current && !(current->data == data))
        {
            parent = current;
            current = (data > current->data) ? current->right : current->left;
        }

        if (!current)
        {
            std::cout << "Node not found!" << std::endl;
            return;
        }

        deleteNode(parent, current);
        std::cout << "Delete successful!" << std::endl;
    }

    void clear()
    {
        destroySubtree(root);
        root = nullptr;
    }

private:
    struct BTNode
    {
        DataType data;
        BTNode *left = nullptr;
        BTNode *right = nullptr;
    };

    BTNode *root = nullptr;

    // 递归插入实现
    void insertNode(BTNode **node, const DataType &data)
    {
        if (!*node)
        {
            *node = new BTNode{data};
            if (!*node)
            {
                std::cerr << "Memory allocation error!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else
            insertNode((data <= (*node)->data) ? &(*node)->left : &(*node)->right, data);
    }

    // 递归销毁子树
    void destroySubtree(BTNode *node)
    {
        if (node)
        {
            destroySubtree(node->left), destroySubtree(node->right);
            delete node;
        }
    }

    // 递归查找节点, 同时加上 const 修饰只读
    BTNode *findNode(BTNode *node, const DataType &target) const
    {
        if (!node)
            return nullptr;
        if (target == node->data)
            return node;
        return target > node->data ? findNode(node->right, target) : findNode(node->left, target);
    }

    // 节点删除核心逻辑
    void deleteNode(BTNode *parent, BTNode *target)
    {
        if (!target->left && !target->right)
        {
            updateParentPointer(parent, target, nullptr);
            delete target;
        }
        else if (!target->left || !target->right)
        {
            BTNode *child = target->left ? target->left : target->right;
            updateParentPointer(parent, target, child);
            delete target;
        }
        else
        {
            BTNode *successor = target->left;
            BTNode *successorParent = target;

            while (successor->right)
            {
                successorParent = successor;
                successor = successor->right;
            }

            target->data = successor->data;
            deleteNode(successorParent, successor);
        }
    }

    // 更新父节点指针
    static inline void updateParentPointer(BTNode *parent, BTNode *target, BTNode *newChild)
    {
        if (!parent)
        {
            // 处理根节点情况需要通过类成员访问，此处需要特殊处理
            // 实际使用中应通过类成员变量直接修改
        }
        else if (parent->left == target)
        {
            parent->left = newChild;
        }
        else
        {
            parent->right = newChild;
        }
    }
};

#endif