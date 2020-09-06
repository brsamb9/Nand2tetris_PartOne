
// have fcommands -> will need to convert the names into their numbers in the symbol table; also ignore the loop instructuions

#include "binary.h"

Binary::Binary(int bit_machine){
    totBits = bit_machine;
    a_c_bits = totBits - 1;
}




char Binary::a_or_c_instr(std::string& typeCommand){
    if (typeCommand.at(0) == '@') {
        return 'A';
    }
    else if (typeCommand.find("=") != -1 || typeCommand.find(";") != -1){
        return 'C';
    };
    return '0';
};


// optcode bit then 15 bits (0 : A Instr; 1 : C Instr)
std::string Binary::num2binary(int numeric, int chosen_num_bits){
    std::string bits = "";
    while (numeric >= 1){
        bits = std::to_string( numeric % 2 ) + bits;
        numeric /= 2;
    }
    if (bits.length() < chosen_num_bits){
        int pad = chosen_num_bits - bits.length();
        std::string padding = "";
        for (int p = 0 ; p < pad ; ++p){
            padding += "0";
        }
        bits = padding + bits;
    }
    return bits;
};

void Binary::encode_A_instr(std::string& typeCommand, std::vector<std::string>& fbinary){
    std::string opCode = "0";
    int num = stoi( typeCommand.substr(1) );
    std::string a_instr_bits = opCode + num2binary(num, a_c_bits);

    fbinary.push_back( a_instr_bits );
};

std::string Binary::c_dest(std::string& typeCommand, int& eqIndx, int& scIndex){
    std::string dest_bits;
    
    if (eqIndx == -1) dest_bits = "000";
    else{
        std::string dest_str = typeCommand.substr(0, eqIndx);
        if (dest_str == "M")  dest_bits = "001";
        else if (dest_str == "D") dest_bits = "010";
        else if (dest_str == "MD") dest_bits = "011";
        else if (dest_str == "A") dest_bits = "100";
        else if (dest_str == "AM") dest_bits = "101";
        else if (dest_str == "AD") dest_bits = "110";
        else if (dest_str == "AMD") dest_bits = "111";
    }
    return dest_bits;
};
std::string Binary::c_comp(std::string& typeCommand, int& eqIndx, int& scIndex){
    std::string comp_str;
    std::string comp_bits;

    if (scIndex != -1 && eqIndx == -1) {
        comp_str = typeCommand.substr(0, scIndex);
    } else if (eqIndx != -1 && scIndex == -1){
        comp_str = typeCommand.substr(eqIndx + 1);

    } else if (eqIndx != -1 && scIndex != -1){
        comp_str = typeCommand.substr(eqIndx + 1, scIndex - 1);
    }
    
    // When there's no compute (i.e. 0;JMP -> compute zero (pg69 in book))
    if (comp_str == "0") {
		comp_bits = "0101010";
	} else if (comp_str == "1") {
		comp_bits = "0111111";
	} else if (comp_str == "-1") {
		comp_bits = "0111010";
	} else if (comp_str == "D") {
		comp_bits = "0001100";
	} else if (comp_str == "A") {
		comp_bits = "0110000";
	} else if (comp_str == "!D") {
		comp_bits = "0001101";
	} else if (comp_str == "!A") {
		comp_bits = "0110001";
	} else if (comp_str == "-D") {
		comp_bits = "0001111";
	} else if (comp_str == "-A") {
		comp_bits = "0110011";
	} else if (comp_str == "D+1" || comp_str == "1+D") {
		comp_bits = "0011111";
	} else if (comp_str == "A+1" || comp_str == "1+A") {
		comp_bits = "0110111";
	} else if (comp_str == "D-1") {
		comp_bits = "0001110";
	} else if (comp_str == "A-1") {
		comp_bits = "0110010";
	} else if (comp_str == "D+A" || comp_str == "A+D") {
		comp_bits = "0000010";
	} else if (comp_str == "D-A") {
		comp_bits = "0010011";
	} else if (comp_str == "A-D") {
		comp_bits = "0000111";
	} else if (comp_str == "D&A" || comp_str == "A&D") {
		comp_bits = "0000000";
	} else if (comp_str == "D|A" || comp_str == "A|D") {
		comp_bits = "0010101";
	} else if (comp_str == "M") {
		comp_bits = "1110000";
	} else if (comp_str == "!M") {
		comp_bits = "1110001";
	} else if (comp_str == "-M") {
		comp_bits = "1110011";
	} else if (comp_str == "M+1" || comp_str == "1+M") {
		comp_bits = "1110111";
	} else if (comp_str == "M-1") {
		comp_bits = "1110010";
	} else if (comp_str == "D+M" || comp_str == "M+D") {
		comp_bits = "1000010";
	} else if (comp_str == "D-M") {
		comp_bits = "1010011";
	} else if (comp_str == "M-D") {
		comp_bits = "1000111";
	} else if (comp_str == "D&M" || comp_str == "M&D") {
		comp_bits = "1000000";
	} else if (comp_str == "D|M" || comp_str == "M|D") {
		comp_bits = "1010101";
	}
    return comp_bits;
};

std::string Binary::c_jump(std::string& typeCommand, int& eqIndx, int& scIndex){
    std::string jump_bits;
    if (scIndex == -1) jump_bits = "000";
    else {
        scIndex += 1;
        std::string jumpTmp = typeCommand.substr(scIndex);

        if (jumpTmp == "JGT") {
            jump_bits = "001";
        } else if (jumpTmp == "JEQ") {
            jump_bits = "010";
        } else if (jumpTmp == "JGE") {
            jump_bits = "011";
        } else if (jumpTmp == "JLT") {
            jump_bits = "100";
        } else if (jumpTmp == "JNE") {
            jump_bits = "101";
        } else if (jumpTmp == "JLE") {
            jump_bits = "110";
        } else if (jumpTmp == "JMP") {
            jump_bits = "111";
        }
    }

    
    return jump_bits;
};




void Binary::encode_C_instr(std::string& typeCommand, std::vector<std::string>& fbinary){
    std::string opCode = "111";


    /* 
    first need to parsed the command further... i'll keep here to avoid unneccasary complication
     can be   -> M=D    /   0;JMP   /   D;JLE   /   MD=A+1;JEQ    /   etc
    */
    int eqSign = typeCommand.find('=');
    int semiCol = typeCommand.find(';');

    std::string dest_3 = c_dest(typeCommand, eqSign, semiCol);
    std::string a_1_comp_6 = c_comp(typeCommand, eqSign, semiCol);
    std::string jump_3 = c_jump(typeCommand, eqSign, semiCol);

    std::string c_instr_bits = opCode + a_1_comp_6 + dest_3 + jump_3;

    fbinary.push_back(c_instr_bits);
};