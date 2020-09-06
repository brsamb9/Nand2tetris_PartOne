/*
C++ symbol table implementation:
- Use of unordered map -> O(1) std::unordered_map<type, type> name; 

Functions:
class constructor -> default input to symbol table
check_table -> checks if pair symbol is in table and overwrites(?)
addPairtoTable -> add pair to symbol table
getAddress -> returns address of variable/loop

*/
#include "symbol_table.h"

symbolTable::symbolTable(){
    // Defaults
    for (int i = 0 ; i < 16; ++i){
        symTab_["R" + std::to_string(i)] = i;
    }
    symTab_["SCREEN"] = 16384;
    symTab_["KBD"] = 24576;

    symTab_["SP"] = 0;
    symTab_["LCL"] = 1;
    symTab_["ARG"] = 2;
    symTab_["THIS"] = 3;
    symTab_["THAT"] = 4;
};


bool symbolTable::check_table(std::string symbolCheck){
    return symTab_.find(symbolCheck) != symTab_.end();
};

void symbolTable::addPairtoTable(std::string symbolName, int symbolAddress){
    if (!check_table(symbolName)){
        symTab_[symbolName] = symbolAddress;
    }
};

void symbolTable::addPairtoTable(std::string symbolName){
    if (!check_table(symbolName)){
        if (n < symTab_["SCREEN"]){
            symTab_[symbolName] = n;
            ++n;
        }
    }
};



int symbolTable::getAddress(std::string symbolName){
  if (check_table(symbolName)) return symTab_[symbolName];
  std::cout << "hih" << std::endl;
  return -1;
};



void symbolTable::printTable(){
    for (auto it = symTab_.begin(); it != symTab_.end() ; ++it){
        std::cout << it->first << " " << it->second << "\n";
    }
};