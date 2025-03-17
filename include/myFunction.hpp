#pragma once
#include "bstree.hpp"

std::string enteringSFZ();
std::string enteringPhone();
void printMainFuction();
const BSTree::DataType getNewData();
void search(BSTree *&T);
void deleteData(BSTree *&T);
void updateData(BSTree *&T);
void importData(BSTree *&T);
void exportData(BSTree *&T);
void printAllData(BSTree *&T);
void enteringNumber(int &a);