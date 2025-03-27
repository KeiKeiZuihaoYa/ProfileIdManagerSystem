#include "myFunction.hpp"

using std::cin;
using std::cout;

/**
 * @brief 从 cin 中得到一个合法的身份证号码
 *
 * @return std::string
 */
std::string enteringSFZ()
{
    std::string id;
    while (cin >> id && validateId(id) == false)
    {
        if (id != "quit")
            cout << "请重新输入正确的身份证号码: ";
        else
            return "";
    }

    if (id[17] == 'x')
        id[17] = 'X';
    return id;
}

/**
 * @brief 从 cin 中得到一个合法的身份证号码
 *
 * @return std::string
 */
std::string enteringPhone()
{
    std::string phone;
    while (cin >> phone && validatePhone(phone) == false)
    {
        cout << "请重新输入正确的手机号码: ";
    }
    return phone;
}

/**
 * @brief 打印主菜单
 *
 */
void printMainFuction()
{
    std::cout << '\n'
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

/**
 * @brief Get the New Data object
 *
 * @return const BSTree::DataType
 */
const BSTree::DataType getNewData()
{
    BSTree::DataType newData;
    cout << "请输入正确的身份证号码: ";
    newData.sfz = enteringSFZ();
    if (newData.sfz == "")
        return newData;
    cout << "请输入正确的姓名: ";
    std::cin >> newData.name;
    cout << "请输入正确的年龄: ";
    cin >> newData.age;
    cout << "请输入正确的手机号码: ";
    newData.phone = enteringPhone();
    cout << "请输入地址: ";
    std::cin >> newData.address;
    return newData;
}

/**
 * @brief The function of search in MainMenu
 *
 * @param T The main tree's address
 */
void search(BSTree *&T)
{
    BSTree::DataType searchId;
    cout << "请输入想要查询的身份证号码: ";
    searchId.sfz = enteringSFZ();
    // quit
    if (searchId.sfz == "")
    {
        cout << "已退出查询操作!\n\n";
        return;
    }
    const BSTree::DataType *searchResult = T->search(searchId);

    if (searchResult == nullptr || searchResult->sfz != searchId.sfz)
    {
        cout << "未查询到对应的信息, 请检查并重试!\n\n";
    }
    else
    {
        cout << "查询成功!\n\n";
        BSTree::print_INFO(searchResult);
    }
}

/**
 * @brief The function of delete in MainMenu
 *
 * @param T The main tree's address
 */
void deleteData(BSTree *&T)
{
    BSTree::DataType deleteId;
    cout << "请输入想要删除信息的身份证号码: ";
    deleteId.sfz = enteringSFZ();
    // quit
    if (deleteId.sfz == "")
    {
        cout << "已退出删除操作!\n\n";
        return;
    }
    T->remove(deleteId);
}

/**
 * @brief The function of update in MainMenu
 *
 * @param T The main tree's address
 */
void updateData(BSTree *&T)
{
    BSTree::DataType updateDataId;
    cout << "请输入想要更改信息的身份证号码: ";
    updateDataId.sfz = enteringSFZ();
    // quit
    if (updateDataId.sfz == "")
    {
        cout << "已退出更新操作!\n\n";
        return;
    }

    if (T->update(updateDataId))
    {
        cout << "更改成功!\n\n";
    }
    else
    {
        cout << "未找到该身份证信息!\n"
             << "更改失败!\n\n";
    }
}

/**
 * @brief The function of importing from a file which has been saved
 *
 * @param T The main tree's address
 */
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

/**
 * @brief The function of exporting date to a file
 *
 * @param T The main tree's address
 */
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

/**
 * @brief The function of printing all data in the main tree
 *
 * @param T The main tree's address
 */
void printAllData(BSTree *&T)
{
    cout << "打印所有数据-> 身份证, 姓名, 手机号码, 地址, 年龄\n";
    T->exportToTerminal();
}

/**
 * @brief 从 cin 中得到一个合法的身份证号码
 *
 * @param a 从 a 中返回
 */
void enteringNumber(int &a)
{
    bool flag = true;
    std::string s;
    while (std::getline(cin, s) && flag)
    {
        flag = a = 0;
        for (auto &i : s)
        {
            a = (a << 3) + (a << 1) + i - '0';
            if (!isdigit(i))
            {
                flag = true;
                break;
            }
        }

        if (!flag)
            return;

        std::cout << "错误：请输入合理数字选项！\n"
                  << "请重新输入: ";
    }
}