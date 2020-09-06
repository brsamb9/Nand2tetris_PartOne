#ifndef BINARY_H
#define BINARY_H
#include <vector>

#include "symbol_table.h"

class Binary{
private:
    int totBits; 
    int a_c_bits;
public:
    Binary(int bit_machine);
    char a_or_c_instr(std::string& typeCommand);

    // optcode bit then 15 bits (0 : A Instr; 1 : C Instr)
    std::string num2binary(int numeric, int bits);

    void encode_A_instr(std::string& typeCommand, std::vector<std::string>& fbinary);

    std::string c_dest(std::string& typeCommand, int& eqIndx, int& scIndex);
    std::string c_comp(std::string& typeCommand, int& eqIndx, int& scIndex);
    std::string c_jump(std::string& typeCommand, int& eqIndx, int& scIndex);
    void encode_C_instr(std::string& typeCommand, std::vector<std::string>& fbinary);
};

#endif