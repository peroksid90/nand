#ifndef HVM_H
#define HVM_H

#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<cctype>

extern std::string name_read_file;

enum COMM_TYPE { C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, NONE };

enum PARS_TYPE { OK, EMPTY, END };

class VMparser
{
    public:
            VMparser(std::string myFile) : ifs(myFile.c_str()), currentComType(NONE) {
                std::string temp = myFile.substr( myFile.rfind("/") + 1 );
                temp.resize( temp.find(".") );
                name_read_file = temp;
            }

            PARS_TYPE advance();

            COMM_TYPE commandType();

            std::string arg1();

            int arg2();

    private:
            std::ifstream ifs;
            std::string in;
            COMM_TYPE currentComType;
};


class CodeWriter
{
    public:
            CodeWriter(std::string myFile) : ofs( myFile.c_str(), std::ios_base::app ), nameFile(myFile.c_str()) {
            }

            //void setFileName(std::string fileName);
            void writeArithmetic(std::string command);
            void writePushPop(COMM_TYPE command, std::string segment, int index);
            void writeInit();
            void writeLabel(std::string label);
            void writeGoto(std::string label);
            void writeIf(std::string label);
            void writeCall(std::string func_name, std::string args_num);
            void writeReturn();
            void writeFunction(std::string func_name, int local_num);
            void setBreakPoint();
    private:
            std::ofstream ofs;
            std::string nameFile;
};
#endif
