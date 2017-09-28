#include <iostream>
#include "Parser.h"

using namespace std;

int main()
{

    Parser *parser = new Parser("in");
    while(parser->hasMoreCommands())
    {
        parser->advance();
        string commandType =  parser->commandType();
        string arg1="";
        int arg2 = -10;
        if( commandType == "empty_line") continue;

        if(commandType != "C_RETURN")
        {
             arg1 = parser->arg1() ;
        }


        if(commandType == "C_PUSH" || commandType == "C_POP"
           || commandType == "C_FUNCTION" || commandType == "C_CALL")
        {
            arg2 = parser->arg2();
        }

        cout << commandType << " " << arg1 << " " << arg2 << endl;
    }
    return 0;
}
