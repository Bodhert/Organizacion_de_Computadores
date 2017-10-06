#include "Parser.h"
#include <regex>
#include <iostream>
#include <fstream>
using namespace std;

regex memoryAccess(R"(((^\s*)(push|pop)\s+(argument|local|static|constant|this|that|pointer|temp)\s+([1-9]\d*|0))(\s*(\/\/.*)?)$)");
regex artihmetics(R"(((^\s*)(add|sub|neg|eq|gt|lt|and|or|not))(\s*(\/\/.*)?)$)");
regex blankLines(R"((^\s*(\/\/.*)?$))");
string currentCommand;
ifstream  file;
map<string,string> c_types;
map<string,string> segment;

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
