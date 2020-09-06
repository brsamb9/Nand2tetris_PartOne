#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "symbol_table.h"

// Parsers job is to convert human readable text into its commands

class Parser{
public:
    // After these two passes -> fcommands should only have field commands with decimal numbers
    std::vector<std::string> clean_up_file(std::string& finput);

    void first_pass(std::vector<std::string> &fcommands, symbolTable& symTable); // check for loop labels
    void second_pass(std::vector<std::string> &fcommands, symbolTable& symTable); // check for variable names


};

#endif