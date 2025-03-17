#include "myFunction.hpp"
#include <string>
#include <iostream>
#include "id_validator.hpp"
#include "phone_validator.hpp"

using std::cin;
using std::cout;

namespace
{
    const std::string enteringSFZ()
    {
        std::string id;
        while (cin >> id && validate(id) == false)
        {
            cout << "请重新输入正确的身份证号码: ";
        }

        if (id[17] == 'x')
            id[17] = 'X';
        return id;
    }

    const std::string enteringPhone()
    {
        std::string phone;
        while (cin >> phone && validate(phone) == false)
        {
            cout << "请重新输入正确的手机号码: ";
        }
        return phone;
    }

    inline void print_INFO(const BSTree::DataType *&data)
    {
        cout << "身份证号码:\t " << data->sfz << '\n'
             << "姓名:\t\t" << data->name << '\n'
             << "年龄:\t\t" << data->age << '\n'
             << "手机号码:\t" << data->phone << '\n';
    }
}

void printMainFuction()
{
    cout << "**********" << '\n';
    cout << "* 1.录入 *" << '\n';
    cout << "* 2.修改 *" << '\n';
    cout << "* 3.查询 *" << '\n';
    cout << "* 4.删除 *" << '\n';
    cout << "* 5.导出 *" << '\n';
    cout << "* 6.导入 *" << '\n';
    cout << "* 7.退出 *" << '\n';
    cout << "**********" << '\n';
    cout << "请输入您想要的操作: ";
}

// 录入新信息
const BSTree::DataType getNewData()
{
    BSTree::DataType newData;
    cout << "请输入正确的身份证号码: ";
    newData.sfz = enteringSFZ();
    cout << "请输入正确的姓名: ";
    cin >> newData.name;
    cout << "请输入正确的年龄: ";
    cin >> newData.age;
    cout << "请输入正确的手机号码: ";
    newData.phone = enteringPhone();
    return newData;
}

void search(BSTree *&T)
{
    BSTree::DataType searchId;
    cout << "请输入想要查询的身份证号码: ";
    searchId.sfz = enteringSFZ();
    const BSTree::DataType *searchResult = T->search(searchId);

    if (searchResult == nullptr || searchResult->sfz != searchId.sfz)
    {
        cout << "未查询到对应的信息, 请检查并重试!\n";
    }
    else
    {
        print_INFO(searchResult);
    }
}

void deleteData(BSTree *&T)
{
    BSTree::DataType deleteId;
    cout << "请输入想要删除信息的身份证号码: ";
    deleteId.sfz = enteringSFZ();
    T->remove(deleteId);
}

void updateData(BSTree *&T)
{
    BSTree::DataType updateDataId;
    cout << "请输入想要更改信息的身份证号码: ";
    updateDataId.sfz = enteringSFZ();

    if (T->update(updateDataId))
    {
        cout << "更改成功!\n";
    }
    else
    {
        cout << "更改失败!\n";
    }
}

void importData(BSTree *&T)
{
    std::string filename;
    cout << "请输入文件路径（可填写相对路径）： ";
    cin >> filename;

    if (T->importFromFile(filename))
    {
        cout << "导入成功!\n";
    }
    else
    {
        cout << "导入失败!\n";
    }
}

void exportData(BSTree *&T)
{
    std::string filename;
    cout << "请输入文件路径（可填写相对路径）： ";
    cin >> filename;

    if (T->exportFromFile(filename))
    {
        cout << "导出成功！\n";
    }
    else
    {
        cout << "文件打开失败！请重试\n";
    }
}

void printAllData(BSTree *&T)
{
}