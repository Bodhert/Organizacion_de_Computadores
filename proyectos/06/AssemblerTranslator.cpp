#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>

using namespace std;

bool isAinstruction(string toParse)
{
    regex Ainstruction("(\\\s*@)[a-zA-Z_$][a-zA-Z_$0-9]*$");
    return regex_match(toParse,Ainstruction);
}

bool isCinstruction(string toParse)
{
 regex Cinstruction("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-)\\\s*(A|D|M|1)");
 regex Cinstruction1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1)\\\s*");
 return regex_match(toParse,Cinstruction) || regex_match(toParse,Cinstruction1);
}

bool isComment(string toParse)
{
    regex simpleComment("\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,simpleComment);
}

bool isEmptyLine(string toParse)
{
    regex blank("\\\s*");
    return regex_match(toParse,blank);
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
        else
        {
           cout << lineCounter << " Not an instrution" << endl;
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
