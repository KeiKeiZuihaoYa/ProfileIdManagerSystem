#ifndef BSTREE_HPP
#define BSTREE_HPP
// bstree.hpp

#include <string>
#include <vector>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem> // C++17 文件系统库

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

    void enteringNumber(int &a)
    {
        while (!(std::cin >> a))
        {
            std::cout << "错误：请输入数字选项！\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    bool add(const DataType &data)
    {
        return insertNode(&root, data);
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
            std::cout << "Node not found!" << "\n\n";
            return;
        }

        deleteNode(root, parent, current);
        std::cout << "Delete successful!" << "\n\n";
    }

    bool update(const DataType &target)
    {
        BTNode *updateNode = updateData(root, target);
        if (updateNode == nullptr)
        {
            return false;
        }
        else
        {
            BTNode _updateData;
            while (1)
            {
                std::cin.clear();                                                   // 清除错误标志
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区
                std::cout << "请输入更改后的姓名: ";
                std::cin >> _updateData.data.name;
                std::cout << "请输入更改后的年龄: ";
                enteringNumber(_updateData.data.age);
                std::cout << "请输入更改后的手机号: ";
                std::cin >> _updateData.data.phone;

                std::cout << "请确认信息:\n";
                inOrderExport(&_updateData, std::cout, "\t");
                std::cout << "\n确认?(Y\\n) ";
                char opt;
                while (std::cin >> opt && !(toupper(opt) == 'Y' || toupper(opt) == 'N'))
                {
                    std::cout << "确认?(Y\\n) ";
                }
                if (toupper(opt) == 'Y')
                {
                    updateNode->data.sfz = _updateData.data.sfz;
                    updateNode->data.name = _updateData.data.name;
                    updateNode->data.phone = _updateData.data.phone;
                    updateNode->data.age = _updateData.data.age;
                    break;
                }
                else
                {
                    continue;
                }
            }
            return true;
        }
    }

    bool importFromFile(const std::string &filename)
    {
        std::ifstream ifs(filename);
        if (!ifs.is_open())
        {
            return false;
        }

        int cnt = 0;
        std::string line, tmp;
        while (std::getline(ifs, line))
        {
            cnt++;
            std::istringstream is(line);
            DataType data;

            if (!std::getline(is, data.sfz, ',') ||
                !std::getline(is, data.name, ',') ||
                !std::getline(is, data.phone, ',') ||
                !std::getline(is, tmp))
            {
                is.clear();
                std::cout << "输入格式错误!\n"
                          << "当前 错误的行数: " << cnt << '\n';
                continue;
            }
            else
                data.age = stoi(tmp);

            add(data);
        }

        ifs.close();
        return true;
    }

    bool exportToFile(const std::string &filename) const
    {
        std::ofstream ofs(filename);
        if (!ofs.is_open())
            return false;

        if (std::filesystem::exists(filename))
        {
            std::cin.clear();                                                   // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区
            std::cout << "文件 \"" << filename << "\" 已存在，是否覆盖？(y/n): ";
            char choice;
            std::cin >> choice;
            std::cin.ignore();

            if (std::tolower(choice) != 'y')
            {
                std::cout << "操作已取消。" << std::endl;
                return false;
            }
        }

        inOrderExport(root, ofs, ",");
        ofs.close();
        return true;
    }

    void exportToTerminal() const
    {
        inOrderExport(root, std::cout, "\t");
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
    bool insertNode(BTNode **node, const DataType &data)
    {
        if (!*node)
        {
            *node = new BTNode{data};
            if (!*node)
            {
                std::cerr << "Memory allocation error!" << std::endl;
                exit(EXIT_FAILURE);
            }
            return true;
        }
        else if (data == (*node)->data)
            return false;
        else
            return insertNode((data <= (*node)->data) ? &(*node)->left : &(*node)->right, data);
    }

    void inOrderExport(BTNode *node, std::ostream &os, std::string S) const
    {
        if (!node)
            return;

        inOrderExport(node->left, os, S);
        os << node->data.sfz << S
           << node->data.name << S
           << node->data.phone << S
           << node->data.age << "\n";
        inOrderExport(node->right, os, S);
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

    BTNode *updateData(BTNode *node, const DataType &target)
    {
        if (!node)
            return nullptr;
        if (target.sfz == node->data.sfz)
            return node;
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