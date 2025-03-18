#include <iostream>
#include <windows.h>
#include "bstree.hpp"
#include "myFunction.hpp"

using std::cin;
using std::cout;
BSTree *T = new BSTree;

signed main()
{
    // std::ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int opt;
    while (1)
    {
        printMainFuction();
        enteringNumber(opt);
        switch (opt)
        {
        case 1: // add
        {
            BSTree::DataType newData = getNewData();
            if (newData.sfz == "") // quit
            {
                cout << "已取消录入操作!\n\n";
                break;
            }

            if (T->add(newData))
            {
                cout << "录入成功!\n\n";
            }
            else
            {
                cout << "录入失败!\n\n";
            }
            break;
        }
        case 2: // update
        {
            updateData(T);
            break;
        }
        case 3: // search
        {
            search(T);
            break;
        }
        case 4: // delete
        {
            deleteData(T);
            break;
        }
        case 6: // import
        {
            importData(T);
            break;
        }
        case 5: // export
        {
            exportData(T);
            break;
        }
        case 7:
        {
            cout << "\n\t祝您生活愉快!\n";
            system("pause");
            goto exi;
        }
        case 8:
        {
            printAllData(T);
            break;
        }
        default:
            cout << "\tError operation! PLZ type a right OPT number." << "\n\n";
            break;
        }
    }
exi:
    return 0;
}