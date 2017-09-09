#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>
#include <cstddef>
#include <fstream>

using namespace std;

map<string,int> symbols;
int variablesPos;

bool isAinstruction(string toParse)
{
    regex Ainstruction("(\\\s*@)([a-zA-Z_$][a-zA-Z_$0-9\\.]*$|([[:digit:]]+))");
    return regex_match(toParse,Ainstruction);
}

bool isCinstruction(string toParse)
{
 regex Cinstruction("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-|&|\\|)\\\s*(A|D|M|1)\\\s*");
 return regex_match(toParse,Cinstruction);
}

bool isCinstruction1(string toParse)
{
   regex Cinstruction1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1|!M|!D|!A)\\\s*");
   return regex_match(toParse,Cinstruction1);
}

bool isCinstruction2(string toParse)
{
 regex Cinstruction2("\\\s*(D|0)\\\s*;\\\s*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP)\\\s*");
 return regex_match(toParse,Cinstruction2);
}

bool isCommentWithInstuctionA(string toParse)
{
    regex Acomment("(\\\s*@)[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,Acomment);
}

bool isCommentWithInstuctionC(string toParse)
{
    regex CinstructionComment("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-)\\\s*(A|D|M|1)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse, CinstructionComment);
}

bool isCommentWithInstuctionC1(string toParse)
{
    regex CinstructionComment1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1|!M|!D|!A)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,CinstructionComment1);
}

bool isCommentWithInstuctionC2(string toParse)
{
    regex CinstructionComment2("\\\s*(D|0)\\\s*;\\\s*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,CinstructionComment2);
}

bool isCommentTag(string toParse)
{
    regex tagComment("\\\s*\\\(\\\s*[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*\\\)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,tagComment);
}


bool isLineComment(string toParse)
{
    regex simpleComment("\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,simpleComment);
}

bool isEmptyLine(string toParse)
{
    regex blank("\\\s*");
    return regex_match(toParse,blank);
}

bool isTag(string toParse)
{
    regex tag("\\\s*\\\(\\\s*[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*\\\)\\\s*");
    return regex_match(toParse,tag);
}

string cleanTag(string TagToclean)
{

    string clean = "";
    size_t firstBracket = TagToclean.find_first_of("(");
    size_t lastBracket = TagToclean.find_last_of(")");

    for(size_t i = firstBracket+1; i < lastBracket; ++i)
    {
        clean += TagToclean[i];
    }

    return clean;
}

string cleanTagWithComments(string TagToclean)
{
    string clean = "";
    size_t firstBracket = TagToclean.find_first_of("(");
    size_t findComment = TagToclean.find_first_of("//");

    for(size_t i = firstBracket+1; i < findComment && TagToclean[i] != ')'; ++i)
    {
        clean += TagToclean[i];
    }

    return clean;

}
void assignTags(string tag, int pos)
{
    symbols[tag] = pos;
}

string cleanAinstruction(string toClean)
{
    string clean = "";
    size_t findAt = toClean.find_first_of("@");
    for(size_t i = findAt+1; i < toClean.size() && toClean[i] != ' '; ++i)
    {
        clean += toClean[i];
    }

    return clean;
}

string encodeAinstruction()
{

}

void initialize()
{
    symbols.clear();
    variablesPos = 16;

    symbols["R0"] = 0;
    symbols["R1"] = 1;
    symbols["R2"] = 2;
    symbols["R3"] = 3;
    symbols["R4"] = 4;
    symbols["R5"] = 5;
    symbols["R6"] = 6;
    symbols["R7"] = 7;
    symbols["R8"] = 8;
    symbols["R9"] = 9;
    symbols["R10"] = 10;
    symbols["R11"] = 11;
    symbols["R12"] = 12;
    symbols["R13"] = 13;
    symbols["R14"] = 14;
    symbols["R15"] = 15;
    symbols["SCREEN"] = 16384;
    symbols["KBD"] = 24576;
    symbols["SP"] = 0;
    symbols["LCL"] = 1;
    symbols["ARG"] = 2;
    symbols["THIS"] = 3;
    symbols["THAT"] = 4;
}

void secondPass(string file)
{
    ifstream fileToRead(file);
	string input;
    int lineCounter = 1;
	int asmLineCounter = 0;
	while(getline(fileToRead,input))
    {
        if(isAinstruction(input))
        {
          string Ains = cleanAinstruction(input);
          cout << Ains << " " << Ains.size() << endl;
        }
    }

     fileToRead.seekg(0,fileToRead.beg);

}

void firstPass(string file)
{
	ifstream fileToRead(file);
	string input;
	int lineCounter = 1;
	int asmLineCounter = 0;
	while(getline(fileToRead,input))
	{
	    if(isTag(input))
        {
            //cout << lineCounter << " tag " << endl;
            string tag = cleanTag(input);
            assignTags(tag,asmLineCounter);
        }
        else if(isCommentTag(input))
        {
            string tag = cleanTagWithComments(input);
            assignTags(tag,asmLineCounter);
        }
        else if(isAinstruction(input))
        {
            //cout << lineCounter << " A instrution" << endl;
            asmLineCounter++;
        }
        else if(isCinstruction(input) || isCinstruction1(input) ||
                isCinstruction2(input))
        {
            //cout << lineCounter << " C instrution" << endl;
            asmLineCounter++;
        }
        else if(isCommentWithInstuctionA(input) || isCommentWithInstuctionC(input)
                || isCommentWithInstuctionC1(input)
                || isCommentWithInstuctionC2(input))
        {
            //cout << lineCounter << " commentary whit insturction" << endl;
            asmLineCounter++;
        }
        else if(isLineComment(input))
        {
            //cout << lineCounter << " line comment " << endl;
        }
        else if(isEmptyLine(input))
        {
            //cout << lineCounter << " Empty Line " << endl;
        }
        else
        {
           cout << "Syntax error: unrecognized expression at line: " << lineCounter << endl;
           break;
        }

        lineCounter++;
	}

    fileToRead.seekg(0,fileToRead.beg);

}

int main(int argc, char* argv[])
{
    initialize();
    if(argv[1] != NULL)
    {
        firstPass(argv[1]);
        secondPass(argv[1]);
    }
    else cout << "The execution should be: .exe nameOfyourfile.asm" << endl;

	return 0;
}
