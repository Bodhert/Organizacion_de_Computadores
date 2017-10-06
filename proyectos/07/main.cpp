#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main()
{

    Parser *parser = new Parser("in");
    CodeWriter *codeWriter = new CodeWriter("in");

    while(parser->hasMoreCommands())
    {
        parser->advance();
        string commandType =  parser->commandType();
        string arg1="";
        int arg2 = -10;

        if(commandType == "Null")
        {
            cout << "bad gramar" << endl;
            break;
        }
        if(commandType == "empty_line") continue;

        if(commandType != "C_RETURN")
        {
             arg1 = parser->arg1();
             if(commandType == "C_ARITHMETIC") codeWriter->writeAritmetic(arg1);
        }

        if(commandType == "C_PUSH" || commandType == "C_POP"
           || commandType == "C_FUNCTION" || commandType == "C_CALL")
        {
            arg2 = parser->arg2();
            if(commandType == "C_PUSH" || commandType == "C_POP")
            {
                codeWriter->writePushPop(commandType,arg1,arg2);
            }
        }

        //cout << commandType << " " << arg1 << " " << arg2 << endl;
    }
    return 0;
}
