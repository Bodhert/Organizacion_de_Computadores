#include "Parser.h"
#include <regex>
#include <iostream>
#include <fstream>
using namespace std;

regex memoryAccess(R"(((^\s*)(push|pop)\s+(argument|local|static|constant|this|that|pointer|temp)\s+([1-9]\d*|0))(\s*(\/\/.*)?)(\r)*$)");
regex artihmetics(R"(((^\s*)(add|sub|neg|eq|gt|lt|and|or|not))(\s*(\/\/.*)?)(\r)*$)");
regex blankLines(R"((^\s*(\/\/.*)?(\r)*$))");
regex labels(R"(((^\s*)label\s+[A-z])\w*(\s*(\/\/.*)?)(\r)*$)");
regex if_goto(R"(((^\s*)if-goto\s+[A-z])\w*(\s*(\/\/.*)?)(\r)*$)");
string currentCommand;
ifstream  file;
map<string,string> c_types;
map<string,string> segment;
int line1 = 0;

//ifstream file ;

Parser::Parser(string file_name)
{
 _file_name = file_name;
 file.open(_file_name);

 c_types["add"] = "C_ARITHMETIC";
 c_types["sub"] = "C_ARITHMETIC";
 c_types["neg"] = "C_ARITHMETIC";
 c_types["eq"] = "C_ARITHMETIC";
 c_types["gt"] = "C_ARITHMETIC";
 c_types["lt"] = "C_ARITHMETIC";
 c_types["and"] = "C_ARITHMETIC";
 c_types["or"] = "C_ARITHMETIC";
 c_types["not"] = "C_ARITHMETIC";
 c_types["push"] = "C_PUSH";
 c_types["pop"] = "C_POP";
 c_types["label"] = "C_LABEL";
 c_types["goto"] = "C_GOTO";
 c_types["if-goto"] = "C_IF";
 c_types["function"] = "C_FUNCTION";
 c_types["call"] = "C_CALL";
 c_types["return"] = "C_RETURN";

 segment["argument"] = "argument";
 segment["local"] = "local";
 segment["static"] = "static";
 segment["constant"] = "constant";
 segment["this"] = "this";
 segment["that"] = "that";
 segment["pointer"] = "pointer";
 segment["temp"] =  "temp";

}

bool Parser::hasMoreCommands()
{
    return !file.eof();
}

void Parser::advance()
{
    getline(file,currentCommand);
    line1++;
}

int Parser::line()
{
    return line1;
}

string Parser::commandType()
{
    smatch words;
    if(regex_match(currentCommand,words,memoryAccess))
    {

        for (unsigned i=0; i<words.size(); ++i)
        {
            string temp = words[i];
            if(c_types.count(temp)) return c_types[temp];
        }
    }
    else if(regex_match(currentCommand,words,artihmetics))
    {
        for (unsigned i=0; i<words.size(); ++i)
        {
            string temp = words[i];
            if(c_types.count(temp)) return c_types[temp];
        }
    }
    else if(regex_match(currentCommand, labels))
    {
         if(c_types.count("label")) return c_types["label"];
    }
    else if(regex_match(currentCommand, if_goto))
    {
        if(c_types.count("if-goto")) return c_types["if-goto"];
    }
    else if(regex_match(currentCommand,blankLines)) return "empty_line";

  return "Null";
}


string Parser::arg1()
{
    smatch words;
    if(regex_match(currentCommand,words,memoryAccess))
    {

        for (unsigned i=0; i<words.size(); ++i)
        {
            string temp = words[i];
            if(segment.count(temp)) return segment[temp];
        }
    }
    else if(regex_match(currentCommand,words,artihmetics))
    {
        for (unsigned i=0; i<words.size(); ++i)
        {
            string temp = words[i];
            if(c_types.count(temp)) return temp;
        }
    }
    else if(regex_match(currentCommand,labels))
    {
        size_t found = currentCommand.find_first_of("label") + 5;
        string temp;
        int posLabel = -1;
        for(size_t i = found; i < currentCommand.size()
            && currentCommand[i] == ' '; ++i)
                posLabel = i+1;

        for(int i = posLabel; (isalnum(currentCommand[i]) ||
            currentCommand[i] == '_') && i < currentCommand.size(); ++i)
                temp += currentCommand[i];

        return temp;
    }
    else if(regex_match(currentCommand, if_goto))
    {
        size_t found = currentCommand.find_first_of("if-goto") + 7;
        string temp;
        int posLabel = -1;
        for(size_t i = found; i < currentCommand.size()
            && currentCommand[i] == ' '; ++i)
                posLabel = i+1;

        for(int i = posLabel; (isalnum(currentCommand[i]) ||
            currentCommand[i] == '_') && i < currentCommand.size(); ++i)
                temp += currentCommand[i];

        return temp;
    }

    return "not found arg1";
}

int Parser::arg2()
{
   smatch words;
    if(regex_match(currentCommand,words,memoryAccess))
    {

        for (unsigned i=0; i<words.size(); ++i)
        {
            string temp = words[i];
            if(isdigit(temp[0])) return atoi(temp.c_str());
        }
    }
}
