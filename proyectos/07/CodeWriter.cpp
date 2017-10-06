#include "CodeWriter.h"
#include <iostream>


using namespace std;

string translate = "";
int artFlag = 0;

CodeWriter::CodeWriter(string out_file_name)
{

}

void CodeWriter::writePushPop(string command,string segment, int index)
{
    string c_PushPop_to_asm;
    string seg;
    if(segment == "local") seg = "R1";
    else if(segment == "argument") seg = "R2";
    else if(segment == "this") seg = "R3";
    else if(segment == "that") seg = "R4";
    else if(segment == "temp") seg = "R" + to_string(index+5);

  if(command == "C_PUSH")
  {

      if(segment == "constant")
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
        else if(segment == "temp")
        {
          c_PushPop_to_asm += "@" + seg +  "\n";
          c_PushPop_to_asm += "D=M\n";
          c_PushPop_to_asm += "@R0\n";
          c_PushPop_to_asm += "A=M\n";
          c_PushPop_to_asm += "M=D\n";
          c_PushPop_to_asm += "@R0\n";
          c_PushPop_to_asm += "M=M+1\n";
          cout << c_PushPop_to_asm;
        }
        else
        {
            c_PushPop_to_asm += "@" + seg + "\n";
            c_PushPop_to_asm += "D=M\n";
            c_PushPop_to_asm += "@" + to_string(index) + "\n";
            c_PushPop_to_asm += "D=D+A\n";
            c_PushPop_to_asm += "A=D\n";
            c_PushPop_to_asm += "D=M\n";
            c_PushPop_to_asm += "@R0\n";
            c_PushPop_to_asm += "A=M\n";
            c_PushPop_to_asm += "M=D\n";
            c_PushPop_to_asm += "@R0\n";
            c_PushPop_to_asm += "M=M+1\n";
            cout << c_PushPop_to_asm;
        }
  }
  else
  {

    if(segment == "temp")
    {
        //error con el segmento temp
        c_PushPop_to_asm += "@R0\n";
        c_PushPop_to_asm += "AM=M-1\n";
        c_PushPop_to_asm += "D=M\n";
        //c_PushPop_to_asm += "@R5\n";
        //c_PushPop_to_asm += "M=D\n";
        c_PushPop_to_asm += "@" + seg + "\n";
        c_PushPop_to_asm += "M=D\n";
        cout << c_PushPop_to_asm;
    }
    else
    {
        c_PushPop_to_asm += "@R0\n";
        c_PushPop_to_asm += "AM=M-1\n";
        c_PushPop_to_asm += "D=M\n";
        c_PushPop_to_asm += "@R5\n";
        c_PushPop_to_asm += "M=D\n";
        c_PushPop_to_asm += "@" + seg + "\n";
        c_PushPop_to_asm += "D=M\n";
        c_PushPop_to_asm += "@" + to_string(index) + "\n";
        c_PushPop_to_asm += "D=D+A\n";
        c_PushPop_to_asm += "@R6\n";
        c_PushPop_to_asm += "M=D\n";
        c_PushPop_to_asm += "@R5\n";
        c_PushPop_to_asm += "D=M\n";
        c_PushPop_to_asm += "@R6\n";
        c_PushPop_to_asm += "A=M\n";
        c_PushPop_to_asm += "M=D\n";
        cout << c_PushPop_to_asm;
    }

  }
}

void CodeWriter::writeAritmetic(string arg)
{
    string aritmetic;
    if(arg == "add")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=D+M\n";
        cout << aritmetic;
    }
    else if(arg == "sub")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=D-M\n";
        aritmetic += "A=A-1\n";
        aritmetic += "M=D\n";
        cout << aritmetic;
    }
    else if(arg == "neg")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "M=-M\n";
        cout << aritmetic;
    }
    else if(arg == "eq")
    {

        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "D=D-M\n";
        aritmetic += "@MAKETRUE" + to_string(artFlag) + "\n";
        aritmetic +=  "D;JEQ\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=0\n";
        aritmetic += "@SKIP" + to_string(artFlag) + "\n";
        aritmetic += "0;JMP\n";
        aritmetic += "(MAKETRUE" + to_string(artFlag) + ")\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=-1\n";
        aritmetic += "(SKIP" + to_string(artFlag) + ")\n";
        artFlag++;
        cout << aritmetic;
    }
    else if(arg == "gt")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "D=D-M\n";
        aritmetic += "@MAKETRUE" + to_string(artFlag) + "\n";
        aritmetic +=  "D;JLT\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=0\n";
        aritmetic += "@SKIP" + to_string(artFlag) + "\n";
        aritmetic += "0;JMP\n";
        aritmetic += "(MAKETRUE" + to_string(artFlag) + ")\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=-1\n";
        aritmetic += "(SKIP" + to_string(artFlag) + ")\n";
        artFlag++;
        cout << aritmetic;
    }
    else if(arg == "lt")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "D=D-M\n";
        aritmetic += "@MAKETRUE" + to_string(artFlag) + "\n";
        aritmetic +=  "D;JGT\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=0\n";
        aritmetic += "@SKIP" + to_string(artFlag) + "\n";
        aritmetic += "0;JMP\n";
        aritmetic += "(MAKETRUE" + to_string(artFlag) + ")\n";
        aritmetic += "@R0\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=-1\n";
        aritmetic += "(SKIP" + to_string(artFlag) + ")\n";
        artFlag++;
        cout << aritmetic;
    }
    else if(arg == "and")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=D&M\n";
        cout << aritmetic;
    }
    else if(arg == "or")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "@R0\n";
        aritmetic += "M=M-1\n";
        aritmetic += "A=M-1\n";
        aritmetic += "M=D|M\n";
        cout << aritmetic;
    }
    else if(arg == "not")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "M=!M\n";
        cout << aritmetic;
    }
}

