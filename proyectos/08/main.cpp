#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

bool ends_withdotVm(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

string generate_out_name(string file)
{
    size_t dot = file.find_first_of(".");
    string outName = "";
    for(size_t i = 0; i < dot ; ++i) outName += file[i];
    return outName;
}

int main(int argc, char* argv[])
{
    if(argv[1] != NULL)
    {
        string file = argv[1];
        if(ends_withdotVm(file,".vm"))
        {
            Parser *parser = new Parser(file);
            string outName = generate_out_name(file);
            CodeWriter *codeWriter = new CodeWriter(outName);
            bool toWrite = true;
            while(parser->hasMoreCommands())
            {
                parser->advance();
                string commandType =  parser->commandType();
                string arg1="";
                int arg2 = -10;

                if(commandType == "Null")
                {
                    cout << "malformed expresion at line : " << parser->line() << endl;
                    toWrite = false;
                    break;
                }
                if(commandType == "empty_line") continue;

                if(commandType != "C_RETURN")
                {
                     arg1 = parser->arg1();
                     if(commandType == "C_ARITHMETIC") codeWriter->writeAritmetic(arg1);
                     else if(commandType == "C_LABEL") codeWriter->writeLabel(arg1);
                     else if(commandType == "C_IF") codeWriter->writeIf(arg1);
                     else if(commandType == "C_GOTO") codeWriter->writeGoto(arg1);
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
            }

            if(toWrite) codeWriter->write();
        } else cout << "only .vm files" << endl;

    } else cout << "no files passed in arguments " << endl;

    return 0;
}
