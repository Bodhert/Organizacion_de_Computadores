#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>

using namespace std;

bool isAinstruction(string toParse)
{
    regex Ainstruction("(\\\s*@)+(([[:digit:]]+)|([[:alpha:]]+))\\\s*");
    return regex_match(toParse,Ainstruction);
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
        else
        {
           cout << lineCounter << " Not A instrution" << endl;
        }

        lineCounter++;
	}

	fclose(stdin);

}

int main(int argc, char* argv[])
{
    int argvSize = sizeof(argv) / sizeof(char*);
    if(argvSize == 1) ReadAndParse(argv[1]);
    else cout << "The execution should be: .exe nameOfyourfile.asm" << endl;

	return 0;
}
