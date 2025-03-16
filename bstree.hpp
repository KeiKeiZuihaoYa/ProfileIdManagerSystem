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

    void add(const DataType &data)
    {
        insertNode(&root, data);
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

        deleteNode(root, parent, current);
        std::cout << "Delete successful!" << std::endl;
    }

    bool update(const DataType &target)
    {
        return updateData(root, target);
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

    bool updateData(BTNode *node, const DataType &target)
    {
        if (!node)
            return false;
        if (target.sfz == node->data.sfz)
        {
            node->data = target;
            return true;
        }
        return target > node->data ? updateData(node->right, target) : updateData(node->left, target);
    }

    // 节点删除核心逻辑
    void deleteNode(BTNode *&root, BTNode *parent, BTNode *target)
    {
        if (target == nullptr)
            return;

        if (!target->left && !target->right)
        {
            // 叶子节点：直接删除，父节点指针置空
            updateParentPointer(root, parent, target, nullptr);
            delete target;
        }
        else if (!target->left || !target->right)
        {
            // 只有一个子节点：用子节点替换目标节点
            BTNode *child = target->left ? target->left : target->right;
            updateParentPointer(root, parent, target, child);
            delete target;
        }
        else
        {
            // 有两个子节点：用前驱节点的值替换，并递归删除前驱
            BTNode *successor = target->left;
            BTNode *successorParent = target;

            while (successor->right)
            {
                successorParent = successor;
                successor = successor->right;
            }

            target->data = successor->data;
            deleteNode(root, successorParent, successor); // 递归删除前驱节点
        }
    }

    // 更新父节点指针
    static inline void updateParentPointer(BTNode *&root, BTNode *parent, BTNode *target, BTNode *newChild)
    {
        if (!parent) // 说明 target 为 root
        {
            root = newChild;
        }
        else
            (parent->left == target ? parent->left : parent->right) = newChild;
    }
};

#endif