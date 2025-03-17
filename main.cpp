#include <iostream>
#include "bstree.hpp"
#include "myFunction.hpp"

using std::cin;
using std::cout;
BSTree *T = new BSTree;

signed main()
{
    std::ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int opt;
    while (1)
    {
        printMainFuction();
        cin >> opt;
        switch (opt)
        {
        case 1: // add
        {
            BSTree::DataType newData = getNewData();
            T->add(newData);
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
        case 5: // import
        {
            importData(T);
            break;
        }
        case 6: // export
        {
            exportData(T);
            break;
        }
        case 7:
        {
            cout << " 祝您生活愉快!";
            goto nxt;
        }
        case 8:
        {
            printAllData(T);
            break;
        }
        default:
            cout << "Error operation! PLZ type a right OPT number." << '\n';
        }
    }
nxt:
    return 0;
}