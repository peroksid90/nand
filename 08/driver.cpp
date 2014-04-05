#include"hvm.h"


void init() {
            CodeWriter code_init("out.asm");
        code_init.writeInit();
}
int main(int argc, char **argv)
{
    std::vector<std::string> arguments;
    for(int i = 1; i < argc; i++) 
        arguments.push_back( argv[i] );
   
    //init();
        
    for(auto iter: arguments) {
            VMparser vm_parser(iter);

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
                if(current_type == C_LABEL) {
                    std::string label = vm_parser.arg1();
                    code_writer.writeLabel(label);
                }
                if(current_type == C_GOTO) {
                    std::string label = vm_parser.arg1();
                    code_writer.writeGoto(label);
                }
                if(current_type == C_IF) {
                    std::string label = vm_parser.arg1();
                    code_writer.writeIf(label);
                }
                if(current_type == C_FUNCTION) {
                    std::string func_name = vm_parser.arg1();
                    int args = vm_parser.arg2();
                    code_writer.writeFunction(func_name, args);
                }
                if(current_type == C_RETURN) {
                    code_writer.writeReturn();
                }
                if(current_type == C_CALL) {
                    std::stringstream arg2;
                    arg2 << vm_parser.arg2();
                    code_writer.writeCall( vm_parser.arg1(), arg2.str() );
                }
                else
                {
                    std::string arg1 = vm_parser.arg1();

                    int arg2 = vm_parser.arg2();

                    code_writer.writePushPop(current_type, arg1, arg2);

                }
                code_writer.setBreakPoint();
            }
    }
    return 0;
}
