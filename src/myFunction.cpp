#include "myFunction.hpp"
#include <string>
#include <iostream>
#include <limits>
#include "id_validator.hpp"
#include "phone_validator.hpp"

using std::cin;
using std::cout;

std::string enteringSFZ()
{
    std::string id;
    while (cin >> id && validateId(id) == false)
    {
        cout << "请重新输入正确的身份证号码: ";
    }

    if (id[17] == 'x')
        id[17] = 'X';
    return id;
}

std::string enteringPhone()
{
    std::string phone;
    while (cin >> phone && validatePhone(phone) == false)
    {
        cout << "请重新输入正确的手机号码: ";
    }
    return phone;
}

inline void print_INFO(const BSTree::DataType *&data)
{
    cout << "查询成功!\n"
         << "身份证号码:\t " << data->sfz << '\n'
         << "姓名:\t\t\t" << data->name << '\n'
         << "年龄:\t\t\t" << data->age << '\n'
         << "手机号码:\t\t" << data->phone << "\n\n";
}

void printMainFuction()
{
    cout << '\n'
         << "*********************" << '\n'
         << "*\t1.录入      *" << '\n'
         << "*\t2.修改      *" << '\n'
         << "*\t3.查询      *" << '\n'
         << "*\t4.删除      *" << '\n'
         << "*\t5.导出      *" << '\n'
         << "*\t6.导入      *" << '\n'
         << "*\t7.退出      *" << '\n'
         << "*********************" << '\n'
         << "请输入您想要的操作: ";
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
        cout << "未查询到对应的信息, 请检查并重试!\n\n";
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
        cout << "更改成功!\n\n";
    }
    else
    {
        cout << "更改失败!\n\n";
    }
}

void importData(BSTree *&T)
{
    std::string filename;
    cout << "请输入文件路径（可填写相对路径）： ";
    cin >> filename;

    if (T->importFromFile(filename))
    {
        cout << "导入成功!\n\n";
    }
    else
    {
        cout << "导入失败!\n\n";
    }
}

void exportData(BSTree *&T)
{
    std::string filename;
    cout << "请输入文件路径（可填写相对路径）： ";
    cin >> filename;

    if (T->exportToFile(filename))
    {
        cout << "导出成功！\n\n";
    }
    else
    {
        cout << "文件打开失败！请重试\n\n";
    }
}

void printAllData(BSTree *&T)
{
    cout << "打印所有数据-> 身份证, 姓名, 手机号码, 年龄\n";
    T->exportToTerminal();
}

void enteringNumber(int &a)
{
    while (!(std::cin >> a))
    {
        std::cout << "错误：请输入合理数字选项！\n"
                  << "请重新输入: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}