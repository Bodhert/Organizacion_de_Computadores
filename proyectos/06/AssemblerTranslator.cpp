#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>

using namespace std;

bool isAinstruction(string toParse)
{
    regex Ainstruction("(\\\s*@)([a-zA-Z_$][a-zA-Z_$0-9\\.]*$|([[:digit:]]+))");
    return regex_match(toParse,Ainstruction);
}

bool isCinstruction(string toParse)
{
 regex Cinstruction("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-|&|\\|)\\\s*(A|D|M|1)\\\s*");
 regex Cinstruction1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1|!M|!D|!A)\\\s*");
 regex Cinstruction2("\\\s*(D|0)\\\s*;\\\s*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP)\\\s*");
 return regex_match(toParse,Cinstruction) || regex_match(toParse,Cinstruction1)
        || regex_match(toParse,Cinstruction2);
}

bool isComment(string toParse)
{
    regex simpleComment("\\\s*//\\\s*.*\\\s*");
    regex Acomment("(\\\s*@)[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*//\\\s*.*\\\s*");
    regex CinstructionComment("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-)\\\s*(A|D|M|1)\\\s*//\\\s*.*\\\s*");
    regex CinstructionComment1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1|!M|!D|!A)\\\s*//\\\s*.*\\\s*");
    regex CinstructionComment2("\\\s*(D|0)\\\s*;\\\s*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP)\\\s*//\\\s*.*\\\s*");
    regex tagComment("\\\s*\\\(\\\s*[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*\\\)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,simpleComment)
            || regex_match(toParse,Acomment)
            || regex_match(toParse, CinstructionComment)
            || regex_match(toParse,CinstructionComment1)
            || regex_match(toParse,CinstructionComment2)
            || regex_match(toParse,tagComment);
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

void ReadAndParse(string file)
{
	freopen(file.c_str(),"r",stdin);
	string input;
	int lineCounter = 1;

	while(getline(cin,input))
	{
	    if(isAinstruction(input))
        {
           cout << lineCounter << " A instrution" << endl;
        }
        else if(isCinstruction(input))
        {
            cout << lineCounter << " C instrution" << endl;
        }
        else if(isEmptyLine(input))
        {
            cout << lineCounter << " Empty Line " << endl;
        }
        else if(isComment(input))
        {
            cout << lineCounter << " commentary " << endl;
        }
        else if(isTag(input))
        {
            cout << lineCounter << " tag " << endl;
        }
        else
        {
           cout << lineCounter << " Not an instrution" << endl;
           break;
        }

        lineCounter++;
	}

	fclose(stdin);

}

int main(int argc, char* argv[])
{
    if(argv[1] != NULL) ReadAndParse(argv[1]);
    else cout << "The execution should be: .exe nameOfyourfile.asm" << endl;

	return 0;
}
