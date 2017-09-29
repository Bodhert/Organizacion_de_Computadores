#include "CodeWriter.h"
#include <iostream>


using namespace std;

string translate = "";

CodeWriter::CodeWriter(string out_file_name)
{

}

void CodeWriter::writePushPop(string command,string segment, int index)
{
    string c_PushPop_to_asm;
  if(command == "C_PUSH")
  {
      c_PushPop_to_asm += "@" + to_string(index) +  "\n";
      c_PushPop_to_asm += "D=A\n";
      c_PushPop_to_asm += "@R0\n";
      c_PushPop_to_asm += "A=M\n";
      c_PushPop_to_asm += "M=D\n";
      c_PushPop_to_asm += "@R0\n";
      c_PushPop_to_asm += "M=M+1\n";
      cout << c_PushPop_to_asm;

  }
  else
  {


  }
}

void CodeWriter::writeAritmetic(string arg)
{
    string aritmetic;
    if(arg == "add")
    {
        aritmetic += "@R0\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=D+M\n";
        cout << aritmetic;
    }
}
