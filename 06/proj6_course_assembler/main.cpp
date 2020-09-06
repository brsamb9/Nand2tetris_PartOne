/*
Main script -> for I/O and driving process

*/

#include <iostream>
#include <fstream> // to read (ifstream) and write (ofstream) from/to files 
#include <vector>


#include "parser.h"
#include "symbol_table.h"
#include "binary.h"

int main(int argc, char *argv[]){

    // Command line check
    if (argc != 2){
        std::cout << "Only one file at a time -> syntax: ./main file.asm\n";
        return -1;
    }
    
    // Opens file and removes whitespaces and comments;
    // Places relevant string commands into a vectors
    std::string finput = argv[1];
    std::string foutput = finput.substr(0, finput.length()-4) + ".hack";

    // Read file -> extract
        

    // Set up  
    Parser parse;
    Binary convert(16);
    symbolTable symTable;

    std::vector<std::string> fcommands;
    std::vector<std::string> fbinary;

    // Initial process -> grab commands in vector format. Populate symbol table with loop and variable declarations
    fcommands = parse.clean_up_file(finput);
    parse.first_pass(fcommands, symTable);
    parse.second_pass(fcommands, symTable);

    // Binary translation - switch in cases
    for (std::string fcom : fcommands){
        std::string binary_command;

        switch (convert.a_or_c_instr(fcom))
        {
        case 'A':
            convert.encode_A_instr(fcom, fbinary);
            break;
        case 'C':
            convert.encode_C_instr(fcom, fbinary);
            break;
        default:
            break;
        }

    }
    

    bool toOutput = true;
    if (toOutput){
        std::ofstream binaryFile ( foutput, std::ofstream::out );
        if (binaryFile){
            for (std::string ele : fbinary){
                binaryFile << ele << "\n";
            }
            binaryFile.close();
        } 

    }
    


    return 0;
}