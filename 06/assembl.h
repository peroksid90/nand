#ifndef ASSEMBL_H
#define ASSEMBL_H
#include <fstream>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <map>
#include "assembl.h"
using std::map;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::string;
using std::bitset;
using std::istringstream;

class Parser 
{
    public:
    Parser(string myFile) : ifs(myFile.c_str()) {}
    
    bool advance()
    {
        if(ifs)
        {
            ifs >> in;
            return true;
        }
        else
        {
            return false;
        }
    }

    void backFile()
    {
        ifs.clear();
        ifs.seekg(0);
    }

    char commandType()
    {
        if(in.find('@') != std::string::npos)
            return 'A';
        else if(in.find('=') != std::string::npos)
            return 'C';
        else if(in.find(';') != std::string::npos)
            return 'C';
        else if(in.find('(') != std::string::npos)
            return 'L';
        else
            return '/';
    }

    string dest()
    {
        if(in.find('=') != std::string::npos)
        {
            return in.substr(0, in.find('='));
        }
        else
        {
            return "null";
        }
    }

    string jump()
    {
        if(in.find(';') != std::string::npos)
        {
            return in.substr(in.find(';')+1);
        }
        else
        {
            return "null";
        }
    }

    string comp()
    {
        if(in.find('=') != std::string::npos)
        {
            return in.substr(in.find('=')+1, in.find(';'));
        }
        else
        {
            return in.substr(0, in.find(';'));
        }
    }



    bool aIsSymbol()
    {
        in.erase(0,1);   //удалить собаку
        if(in.find_first_not_of("1234567890") != string::npos)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void removeBKT() 	//удалить скобки
    {
        in.erase(0,1);
        in.erase(in.size()-1, 1);
    }

    bool aIsUpper()
    {
        for(int i = 0; i < in.size(); i++)
        {
            if( islower(in[i]) )
            {
                    return false;
            }
        }

        return true;
    }

    string aSymbol()
    {
        return in;
    }

    int aInteger()
    {
        istringstream is(in);
        int i;
        is >> i;
        return i;
    }
    
    private:
    string in;
    ifstream ifs;

};

class SymbolTable
{
    public:
	    SymbolTable()
	    {
    		addEntry("SP", 0);
    		addEntry("LCL", 1);
    		addEntry("ARG", 2);
    		addEntry("THIS", 3);
    		addEntry("THAT", 4);
    		addEntry("R0", 0);
    		addEntry("R1", 1);
    		addEntry("R2", 2);
    		addEntry("R3", 3);
   		addEntry("R4", 4);
    		addEntry("R5", 5);
    		addEntry("R6", 6);
    		addEntry("R7", 7);
    		addEntry("R8", 8);
    		addEntry("R9", 9);
    		addEntry("R10", 10);
    		addEntry("R11", 11);
    		addEntry("R12", 12);
    		addEntry("R13", 13);
    		addEntry("R14", 14);
    		addEntry("R15", 15);
    		addEntry("SCREEN", 16384);
    		addEntry("KBD", 24576);
	    }
    
            void addEntry(string symb, int addr)
            {
                table[symb] = addr;
            }

            bool contains(string symb)
            {
                if(table.count(symb))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            int getAddress(string symb)
            {
                return table[symb];
            }

    private:
            
            map<string, int> table;
};

class Code
{
    public:
            string dest(string mnemon)
            {
                if(mnemon == "null")
                    return "000";
                else if(mnemon == "M")
                    return "001";
                else if(mnemon == "D")
                    return "010";
                else if(mnemon == "MD")
                    return "011";
                else if(mnemon == "A")
                    return "100";
                else if(mnemon == "AM")
                    return "101";
                else if(mnemon == "AD")
                    return "110";
                else if(mnemon == "AMD")
                    return "111";
                else
                    abort();
            }
            
            string jump(string mnemon)
            {
                if(mnemon == "null")
                    return "000";
                else if(mnemon == "JGT")
                    return "001";
                else if(mnemon == "JEQ")
                    return "010";
                else if(mnemon == "JGE")
                    return "011";
                else if(mnemon == "JLT")
                    return "100";
                else if(mnemon == "JNE")
                    return "101";
                else if(mnemon == "JLE")
                    return "110";
                else if(mnemon == "JMP")
                    return "111";
                else
                    abort();
            }

            
            string comp(string mnemon)
            {
                if(mnemon == "0")
                    return "0101010";
                else if(mnemon == "1")
                    return "0111111";
                else if(mnemon == "-1")
                    return "0111010";
                else if(mnemon == "D")
                    return "0001100";
                else if(mnemon == "A")
                    return "0110000";
                else if(mnemon == "!D")
                    return "0001101";
                else if(mnemon == "!A")
                    return "0110001";
                else if(mnemon == "-D")
                    return "0001111";
                else if(mnemon == "-A")
                    return "0110011";
                else if(mnemon == "D+1")
                    return "0011111";
                else if(mnemon == "A+1")
                    return "0110111";
                else if(mnemon == "D-1")
                    return "0001110";
                else if(mnemon == "A-1")
                    return "0110010";
                else if(mnemon == "D+A")
                    return "0000010";
                else if(mnemon == "D-A")
                    return "0010011";
                else if(mnemon == "A-D")
                    return "0000111";
                else if(mnemon == "D&A")
                    return "0000000";
                else if(mnemon == "D|A")
                    return "0010101";
                else if(mnemon == "M")
                    return "1110000";
                else if(mnemon == "!M")
                    return "1110001";
                else if(mnemon == "-M")
                    return "1110011";
                else if(mnemon == "M+1")
                    return "1110111";
                else if(mnemon == "M-1")
                    return "1110010";
                else if(mnemon == "D+M")
                    return "1000010";
                else if(mnemon == "D-M")
                    return "1010011";
                else if(mnemon == "M-D")
                    return "1000111";
                else if(mnemon == "D&M")
                    return "1000000";
                else if(mnemon == "D|M")
                    return "1010101";
                else
                    abort();
            }
};
#endif
