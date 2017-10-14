#include "CodeWriter.h"
#include <iostream>
#include <fstream>

using namespace std;

string translate = "";
int artFlag = 0;

CodeWriter::CodeWriter(string out_file_name)
{
    _out_file = out_file_name + ".asm";
}

void CodeWriter::write()
{

    ofstream out(_out_file);
    out << translate;
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
    else if(segment == "pointer") seg = "R" + to_string(index+3);
    else if(segment == "static") seg = to_string(index+16);

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
          translate += c_PushPop_to_asm;
          //cout << c_PushPop_to_asm;
        }
        else if(segment == "temp" || segment == "pointer" || segment == "static")
        {
          c_PushPop_to_asm += "@" + seg +  "\n";
          c_PushPop_to_asm += "D=M\n";
          c_PushPop_to_asm += "@R0\n";
          c_PushPop_to_asm += "A=M\n";
          c_PushPop_to_asm += "M=D\n";
          c_PushPop_to_asm += "@R0\n";
          c_PushPop_to_asm += "M=M+1\n";
          translate += c_PushPop_to_asm;
          //cout << c_PushPop_to_asm;
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
            translate += c_PushPop_to_asm;
            //cout << c_PushPop_to_asm;
        }
  }
  else
  {

    if(segment == "temp" || segment == "pointer" || segment == "static")
    {
        c_PushPop_to_asm += "@R0\n";
        c_PushPop_to_asm += "AM=M-1\n";
        c_PushPop_to_asm += "D=M\n";
        c_PushPop_to_asm += "@" + seg + "\n";
        c_PushPop_to_asm += "M=D\n";
        translate += c_PushPop_to_asm;
        //cout << c_PushPop_to_asm;
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
        translate += c_PushPop_to_asm;
        //cout << c_PushPop_to_asm;
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
        translate += aritmetic;
        //cout << aritmetic;
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
        translate += aritmetic;
        //cout << aritmetic;
    }
    else if(arg == "neg")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "M=-M\n";
        translate += aritmetic;
        //cout << aritmetic;
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
        translate += aritmetic;
        //cout << aritmetic;
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
        translate += aritmetic;
        //cout << aritmetic;
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
        translate += aritmetic;
        //cout << aritmetic;
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
        translate += aritmetic;
        //cout << aritmetic;
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
        translate += aritmetic;
        //cout << aritmetic;
    }
    else if(arg == "not")
    {
        aritmetic += "@R0\n";
        aritmetic += "A=M\n";
        aritmetic += "D=A-1\n";
        aritmetic += "A=D\n";
        aritmetic += "D=M\n";
        aritmetic += "M=!M\n";
        translate += aritmetic;
        //cout << aritmetic;
    }
}

void CodeWriter::writeLabel(string label)
{
    translate += "(" + label + ")\n";
}

void CodeWriter::writeIf(string label)
{
    string if_goto;
    if_goto += "@R0\n";
    if_goto += "AM=M-1\n";
    if_goto += "D=M\n";
    if_goto += "@" + label + "\n";
    if_goto += "D;JNE\n";
    translate += if_goto;
}

