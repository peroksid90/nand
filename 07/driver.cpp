#include"hvm.h"

int main(int argc, char **argv)
{
    VMparser vm_parser(argv[1]);
    
    CodeWriter code_writer("out.asm");
   
    PARS_TYPE pars_type;

    while(pars_type = vm_parser.advance(), pars_type != END)
    {
        if(pars_type == EMPTY)
            continue;

        COMM_TYPE current_type = vm_parser.commandType();
        
        if(current_type == C_ARITHMETIC)
        {
            std::string my_self = vm_parser.arg1();
            
            code_writer.writeArithmetic(my_self);
        }
        else
        {
            std::string arg1 = vm_parser.arg1();
            
            int arg2 = vm_parser.arg2();

            code_writer.writePushPop(current_type, arg1, arg2);
    
        }
    }
    return 0;
}
