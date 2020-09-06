/*
Parser - takes file-> outputs stringstream of important information

*/
#include "parser.h"
#include "symbol_table.h"


std::vector<std::string> Parser::clean_up_file(std::string& finput){

    std::ifstream asmFile ( finput );
    std::vector<std::string> asm_lines;

    std::string fline;
    while (std::getline(asmFile, fline)){
        std::stringstream stream(fline);
        std::string tmp;

        std::string words = "";
        while(stream >> tmp){
            if (tmp[0] == '/' && tmp[1] == '/') break;

            words += tmp;
        }
        if (words != "") asm_lines.push_back(words);
    };
    asmFile.close();

    return asm_lines;
};

void Parser::first_pass(std::vector<std::string> &fcommands, symbolTable& symTable){
    int lineNum { 0 };
    for (int i = 0 ; i < fcommands.size(); ++i){
        if (fcommands[i].at(0) == '('){
                int start_slice = fcommands[i].find('(') + 1;
                int end_slice = fcommands[i].find(')') - 1;
                std::string loopName = fcommands[i].substr( start_slice, end_slice);

                // no ++lineNum here -> (loop) is a psuedo command
                if (!symTable.check_table(loopName)){                    
                    symTable.addPairtoTable(loopName, lineNum);
                }
                // Erase psuedo code from vector
                fcommands.erase(fcommands.begin() + i );

                // consectutive labels
                if (i != fcommands.size()-1){
                    if (fcommands[i].at(0) == '('){
                        --i;
                        --lineNum;
                    }
                }
                
        } 
        ++lineNum;
    }
};

void Parser::second_pass(std::vector<std::string> &fcommands, symbolTable& symTable){
    // Check only for user-defined variables
    for (int i = 0 ; i < fcommands.size(); ++i){
        std::string fline = fcommands[i];
        if (fline.at(0) == '@' && (bool)std::isalpha( fline.at(1) ) ){
                std::string varName = fline.substr( 1 );
                
                if (!symTable.check_table(varName)){
                    // Add pair without an int argument -> set to addres n (16++)
                    symTable.addPairtoTable(varName);
                }
                // To their respective numbers
                fcommands[i] = "@" + std::to_string( symTable.getAddress(varName) );

        } 

    }
}; 
