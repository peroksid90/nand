#include "hvm.h"

PARS_TYPE VMparser::advance()
{

    if(ifs.eof())
    {
        return END;
    }

        std::string temp;
        
        std::getline(ifs, temp);

        std::string clear(temp, 0, temp.find("/"));
    
    if(clear.empty() || !isprint(clear[0]))
    {
        return EMPTY;
    }
         
        in = clear;
        return OK;
}

COMM_TYPE VMparser::commandType()
{

    if(in.find("add") != std::string::npos || in.find("sub") != std::string::npos 
       || in.find("neg") != std::string::npos || in.find("eq") != std::string::npos
       || in.find("gt") != std::string::npos || in.find("lt") != std::string::npos
       || in.find("and") != std::string::npos || in.find("or") != std::string::npos
       || in.find("not") != std::string::npos) 
    {
        currentComType = C_ARITHMETIC;
        return C_ARITHMETIC;
    }

    if(in.find("push") != std::string::npos)
    {
        currentComType = C_PUSH;
        return C_PUSH;
    }

    if(in.find("pop") != std::string::npos)
    {
        currentComType = C_POP;
        return C_POP;
    }
    else
        std::cerr << "Unknown command type\n";
}


std::string VMparser::arg1()
{
    std::string arg;
    
    if(currentComType == C_ARITHMETIC)
    {
        std::istringstream instr(in);
        instr >> arg;
        std::cerr << "currentComType == C_ARITHMETIC: " << arg << "\n";
    }
    else
    {
        std::istringstream instr(in);
        std::string dump;
        instr >> dump >> arg;
    }
    return arg;
}

int VMparser::arg2()
{
    std::istringstream instr(in);
    int arg;
    std::string dump;
    instr >> dump >> dump >> arg;
    return arg;
}


void CodeWriter::writeArithmetic(std::string command)
{
    static int Un = 0; //Unic lablel

    if(command == "add")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "M=M+D\n"
                  << "@SP\n"
                  << "M=M+1\n";
    
    if(command == "sub")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "M=M-D\n"
                  << "@SP\n"
                  << "M=M+1\n";
    
    if(command == "neg")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "M=!M\n"
                  << "@SP\n"
                  << "M=M+1\n";
    
    if(command == "eq")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M-D\n"
                  << "@TRUE" << Un << "\n"
                  << "D;JEQ\n"
                  << "@FALSE" << Un << "\n"
                  << "0;JMP\n"
                  << "(TRUE" << Un << ")\n"
                  << "@SP\n"
                  << "A=M\n"
                  << "M=-1\n"
                  << "@DONE" << Un << "\n"
                  << "0;JMP\n"
                  << "(FALSE" << Un << ")\n"
                  << "@SP\n"
                  << "A=M\n"
                  << "M=0\n"
                  << "(DONE" << Un << ")\n"
                  << "@SP\n"
                  << "M=M+1\n";


    
    if(command == "gt")
               ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M-D\n"
                  << "@TRUE" << Un << "\n"
                  << "D;JGT\n"
                  << "@FALSE" << Un << "\n"
                  << "0;JMP\n"
                  << "(TRUE" << Un << ")\n"
                  << "@SP\n"
                  << "A=M\n"
                  << "M=-1\n"
                  << "@DONE" << Un << "\n"
                  << "0;JMP\n"
                  << "(FALSE" << Un << ")\n"
                  << "@SP\n"
                  << "A=M\n"
                  << "M=0\n"
                  << "(DONE" << Un << ")\n"
                  << "@SP\n"
                  << "M=M+1\n";
  
       
    
    if(command == "lt")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M-D\n"
                  << "@TRUE" << Un << "\n"
                  << "D;JLT\n"
                  << "@FALSE" << Un << "\n"
                  << "0;JMP\n"
                  << "(TRUE" << Un << ")\n"
                  << "@SP\n"
                  << "A=M\n"
                  << "M=-1\n"
                  << "@DONE" << Un << "\n"
                  << "0;JMP\n"
                  << "(FALSE" << Un << ")\n"
                  << "@SP\n"
                  << "A=M\n"
                  << "M=0\n"
                  << "(DONE" << Un << ")\n"
                  << "@SP\n"
                  << "M=M+1\n";
     
    if(command == "and")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "M=M&D\n"
                  << "@SP\n"
                  << "M=M+1\n";
     
    if(command == "or")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "D=M\n"
                  << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "M=M|D\n"
                  << "@SP\n"
                  << "M=M+1\n";
    
    if(command == "not")
              ofs << "@SP\n"
                  << "M=M-1\n"
                  << "A=M\n"
                  << "M=!M\n"
                  << "M=M+1\n"
                  << "@SP\n"
                  << "M=M+1\n";
    Un++;

}

void CodeWriter::writePushPop(COMM_TYPE command, std::string segment, int index) 
{
    if(command == C_PUSH && segment == "pointer")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@THIS\n"
            << "A=A+D\n"
            << "A=M\n"
            << "D=A\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";

    if(command == C_PUSH && segment == "constant")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";

    if(command == C_PUSH && segment == "local")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@LCL\n"
            << "A=M+D\n"
            << "D=M\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";
    
    if(command == C_PUSH && segment == "argument")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@ARG\n"
            << "A=M+D\n"
            << "D=M\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";
    
    if(command == C_PUSH && segment == "this")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@THIS\n"
            << "A=M+D\n"
            << "D=M\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";
    
    if(command == C_PUSH && segment == "that")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@THAT\n"
            << "A=M+D\n"
            << "D=M\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";

    if(command == C_PUSH && segment == "temp")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@R5\n"
            << "A=A+D\n"
            << "D=M\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";

    if(command == C_PUSH && segment == "static")
        ofs << "@" << nameFile + "." << index << "\n"
            << "D=M\n"
            << "@SP\n"
            << "A=M\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M+1\n";

    if(command == C_POP && segment == "pointer")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@THIS\n"
            << "D=A+D\n"
            << "@R13\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M-1\n"
            << "A=M\n"
            << "D=M\n"
            << "@R13\n"
            << "A=M\n"
            << "M=D\n";


    if(command == C_POP && segment == "local")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@LCL\n"
            << "D=M+D\n"
            << "@R13\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M-1\n"
            << "A=M\n"
            << "D=M\n"
            << "@R13\n"
            << "A=M\n"
            << "M=D\n";

    if(command == C_POP && segment == "argument")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@ARG\n"
            << "D=M+D\n"
            << "@R13\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M-1\n"
            << "A=M\n"
            << "D=M\n"
            << "@R13\n"
            << "A=M\n"
            << "M=D\n";
    
    if(command == C_POP && segment == "this")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@THIS\n"
            << "D=M+D\n"
            << "@R13\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M-1\n"
            << "A=M\n"
            << "D=M\n"
            << "@R13\n"
            << "A=M\n"
            << "M=D\n";
    
    if(command == C_POP && segment == "that")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@THAT\n"
            << "D=M+D\n"
            << "@R13\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M-1\n"
            << "A=M\n"
            << "D=M\n"
            << "@R13\n"
            << "A=M\n"
            << "M=D\n";
    
    if(command == C_POP && segment == "temp")
        ofs << "@" << index << "\n"
            << "D=A\n"
            << "@R5\n"
            << "D=A+D\n"
            << "@R13\n"
            << "M=D\n"
            << "@SP\n"
            << "M=M-1\n"
            << "A=M\n"
            << "D=M\n"
            << "@R13\n"
            << "A=M\n"
            << "M=D\n";

    if(command == C_POP && segment == "static")
        ofs  << "@SP\n"
             << "M=M-1\n"
             << "A=M\n"
             << "D=M\n"
             << "@" << nameFile + "." << index << "\n"
             << "M=D\n";
}
