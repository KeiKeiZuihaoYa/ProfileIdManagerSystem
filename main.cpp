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
        myFunction::printMainFuction();
        cin >> opt;
        switch (opt)
        {
        case 1: // add
        {
            BSTree::DataType newData = myFunction::getNewData();
            T->add(newData);
            break;
        }
        case 2: // update
        {
            myFunction::updateData(T);
            break;
        }
        case 3: // search
        {
            myFunction::search(T);
            break;
        }
        case 4: // delete
        {
            myFunction::deleteData(T);
            break;
        }
        case 5: // import
        {
            myFunction::import(T);
            break;
        }
        case 6: // export
        {
            myFunction::export(T);
            break;
        }
        case 7:
        {
            cout << " 祝您生活愉快!";
            goto nxt;
        }
        default:
            cout << "Error operation! PLZ type a right OPT number." << '\n';
        }
    }
nxt:
    return 0;
}