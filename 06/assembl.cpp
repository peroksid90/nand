#include "assembl.h"

int main(int argc, char *argv[])
{
	string ar(argv[1]);
        string goPerl = "perl perl.pl "+ar;
	system(goPerl.c_str());

        Parser p("out.txt");
    	Code code;
    	SymbolTable myTable;
    
        int address = 16;
    	int counter = 0;
    
    //Записали в таблицу все лейбы
    while(p.advance())
    {

        char Type = p.commandType();
        switch(Type)
        {
            case 'A' : 
                ++counter;
                break;
            
            case 'C' :
                ++counter;
                break;

            case 'L' :
                if(p.removeBKT(), !myTable.contains(p.aSymbol()) )
                {
                    myTable.addEntry(p.aSymbol(), counter);
                }
            	break;
        }

    }

                	             

    p.backFile(); //Вернуть указатель на начало файла

    //Записали в таблицу все А-переменные
    while(p.advance())
    {
        char Type = p.commandType();
        switch(Type)
        {
            case 'A' :
    if( p.aIsSymbol() && !myTable.contains(p.aSymbol()) && !p.aIsUpper() )
                	{
                    		myTable.addEntry(p.aSymbol(), address);
                    		++address;
               		}
        break;
 
        }
    }

    p.backFile(); //Вернуть указатель на начало файла
    
    ofstream ofs("out.hack");

    //Заменили все значения битами
    while(p.advance())
    {
        char Type = p.commandType();
        switch(Type)
        {
            case 'A' : 
p.aIsSymbol() ? ofs << bitset<16>( myTable.getAddress(p.aSymbol()) ) << "\n" : ofs << bitset<16>( p.aInteger() ) << "\n";
                break;
            
            case 'C' :
                ofs << "111" 
		     << code.comp(p.comp()) 
		     << code.dest(p.dest()) 
		     << code.jump(p.jump()) 
		     << "\n"; 
                break;
        }
    }
}
