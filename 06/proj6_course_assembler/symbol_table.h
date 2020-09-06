#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>

class symbolTable
{
public:
    int n {16};
    std::unordered_map<std::string, int> symTab_;

    symbolTable();

    bool check_table(std::string symbolCheck);
    
    void addPairtoTable(std::string symbolName, int symbolAddress);
    void addPairtoTable(std::string symbolName);

    int getAddress(std::string symbolName);

    void printTable();
};


#endif